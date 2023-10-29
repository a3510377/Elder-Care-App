#include <Adafruit_ADXL345_U.h>
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <FallDetection.h>
#include <HTTPClient.h>
#include <PulseSensor.h>
#include <SPIFFS.h>
#include <StepCount.h>
#include <Wire.h>
#include <esp_adc_cal.h>

#include "app/display.h"
#include "network.h"
#include "utils/info.h"
#include "variable.h"

PulseSensor pulse(33, 27);
Adafruit_BMP085 bmp;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
FallDetection fallDetection;
StepCount step;
Display screen;
Network network;
HTTPClient http;

ulong last_time = 0;
bool warning, old_fall_status;
int vibration_warn_delay;
uint base_vibration_warn_delay;
SemaphoreHandle_t lvgl_mutex = xSemaphoreCreateMutex();

void TaskTFT(void *) {
  while (1) {
    xSemaphoreTake(lvgl_mutex, portMAX_DELAY);
    lv_timer_handler();
    xSemaphoreGive(lvgl_mutex);
    vTaskDelay(1);
  }
}

void postJson(String data) {
  WiFiClient client;

  String id = network.getWifiConfig().ID;
  http.begin(client, String(SERVER_ADDRESS) + "/api/devices/" + id);
  http.addHeader("Content-Type", "application/json");

  Serial.print("post data: ");
  Serial.println(data);
  int status = http.POST(data);
  if (status != 200) {
    Serial.print(F("post info error: "));
    Serial.println(status);
  }
}

void postInfo(StateInfo *info) {
  if (!info->pulse.state()) return;

  ulong now = millis();
  if (last_time + 6e4 < now || !last_time) {
    last_time = now;

    String data = "{";
    data += "\"temp\":";
    data += String(parseTemperature(info));
    data += ",\"heartbeat\":";
    data += String(parseHeart(info));
    data += ",\"stepCount\":";
    data += String(info->stepCount.get_step());
    data += "}";

    postJson(data);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(NOTIFY_PIN, OUTPUT);
  digitalWrite(NOTIFY_PIN, LOW);
  delay(500);
  digitalWrite(NOTIFY_PIN, HIGH);

  if (Wire.begin(15, 13)) {
    Serial.println(F("i2c connected"));
  }

  if (!SPIFFS.begin(true)) {
    Serial.println(F("An error occurred while mounting SPIFFS"));

    return;
  }

  if (!bmp.begin()) {
    Serial.println(
        F("Could not find a valid BMP085/BMP180 sensor, check wiring!"));
    while (1)
      ;
  }

  if (!accel.begin()) {
    Serial.println(F("No ADXL345 sensor detected."));
    while (1)
      ;
  }

  screen.init();
  screen.setup_app();
  fallDetection.set_handler(
      []() { postJson(F("{\"warn\":{\"fall\":true}}")); });

  xTaskCreatePinnedToCore(TaskTFT, "TaskTFT", 4096, NULL, 0, NULL, 1);

  network.init();
  pulse.begin();
  step.init();
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);

  if (touchRead(4) <= 80) {
    if (!pulse.state()) pulse.start();

    pulse.read();

    float total_acceleration =
        sqrt(sq(event.acceleration.x) + sq(event.acceleration.y) +
             sq(event.acceleration.z));
    step.loop(total_acceleration);
    fallDetection.loop(total_acceleration);
  } else if (pulse.state()) pulse.stop();

  StateInfo info = StateInfo {
      .pulse = pulse,
      .bpm085 = bmp,
      .fallDetection = fallDetection,
      .stepCount = step,
      event = event,
  };
  screen.run_app(&info);
  network.autoUpdateNTP();
  postInfo(&info);

  if (fallDetection.has_falling()) {
    if (!warning) {
      warning = true;
      vibration_warn_delay = 0;
      base_vibration_warn_delay = 20;
    }
    if (!digitalRead(BTN_PIN)) {
      fallDetection.close_warning();
    }
    old_fall_status = true;
  } else if (old_fall_status) old_fall_status = warning = false;

  if (warning) {
    digitalWrite(NOTIFY_PIN, vibration_warn_delay > 0);

    if (vibration_warn_delay < 0 &&
        base_vibration_warn_delay < -vibration_warn_delay) {
      vibration_warn_delay = base_vibration_warn_delay;
    }

    vibration_warn_delay--;
  } else digitalWrite(NOTIFY_PIN, HIGH);

  vTaskDelay(10);
}
