#include <Adafruit_ADXL345_U.h>
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <PulseSensor.h>
#include <SPIFFS.h>
#include <WebSocketsClient.h>
#include <Wire.h>

#include "app/display.h"
#include "network.h"
#include "variable.h"

WebSocketsClient webSocket;
PulseSensor pulse(33, 27);
Adafruit_BMP085 bmp;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
Display screen;
Network network;

SemaphoreHandle_t lvgl_mutex = xSemaphoreCreateMutex();

void TaskTFT(void *) {
  while (1) {
    xSemaphoreTake(lvgl_mutex, portMAX_DELAY);
    lv_timer_handler();
    xSemaphoreGive(lvgl_mutex);
    vTaskDelay(1);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(NOTIFY_PIN, OUTPUT);
  digitalWrite(NOTIFY_PIN, LOW);
  delay(500);
  digitalWrite(NOTIFY_PIN, HIGH);

  if (Wire.begin(15, 13)) {
    Serial.println("i2c connected");
  }

  if (!SPIFFS.begin(true)) {
    Serial.println(F("An error occurred while mounting SPIFFS"));

    return;
  }

  if (!bmp.begin()) {
    Serial.println(
        "Could not find a valid BMP085/BMP180 sensor, check wiring!");
    while (1)
      ;
  }

  if (!accel.begin()) {
    Serial.println("No ADXL345 sensor detected.");
    while (1)
      ;
  }

  analogReadResolution(10);

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
  StateInfo info = StateInfo {pulse, bmp, event};

  screen.run_app(&info);
  network.autoUpdateNTP();

  vTaskDelay(10);

  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;
  float totalAcceleration = sqrt(x * x + y * y + z * z);

  Serial.print("X:");
  Serial.print(x);
  Serial.print(",Y:");
  Serial.print(y);
  Serial.print(",Z:");
  Serial.print(z);
  Serial.print(",A:");
  Serial.print(totalAcceleration);

  Serial.print(",GX:");
  Serial.print(event.gyro.x);
  Serial.print(",GY:");
  Serial.print(event.gyro.y);
  Serial.print(",GZ:");
  Serial.println(event.gyro.z);
}
