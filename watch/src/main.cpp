#include <Adafruit_ADXL345_U.h>
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <FallDetection.h>
#include <HTTPClient.h>
#include <PulseSensor.h>
#include <SPIFFS.h>
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
Display screen;
Network network;
HTTPClient http;

SemaphoreHandle_t lvgl_mutex = xSemaphoreCreateMutex();

void TaskTFT(void *) {
  while (1) {
    xSemaphoreTake(lvgl_mutex, portMAX_DELAY);
    lv_timer_handler();
    xSemaphoreGive(lvgl_mutex);
    vTaskDelay(1);
  }
}

void postJsonData(String data) {
  WiFiClient client;

  http.begin(client, String(SERVER_ADDRESS) + "/api/devices/");
  http.addHeader("Content-Type", "application/json");
  http.POST(data);
}

void postInfo(StateInfo *info) {
  static ulong last_time = 0;
  if (!info->pulse.state()) return;

  ulong now = millis();
  if (now - last_time > 3e4) last_time = now;

  String data = "{";
  data += "\"";
  data += "}";
  postJsonData(data);
}

void setup() {
  Serial.begin(9600);

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

  network.init();
  pulse.begin();
  screen.init();
  screen.setup_app();

  xTaskCreatePinnedToCore(TaskTFT, "TaskTFT", 4096, NULL, 0, NULL, 1);
}

void loop() {
  if (touchRead(4) <= 50) {
    if (!pulse.state()) pulse.start();

    pulse.read();
  } else if (pulse.state()) pulse.stop();

  sensors_event_t event;
  accel.getEvent(&event);
  fallDetection.loop(event);
  StateInfo info = StateInfo {pulse, bmp, fallDetection, event};

  screen.run_app(&info);
  network.autoUpdateNTP();

  vTaskDelay(10);
}
