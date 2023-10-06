#include "main.h"

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
  pulse.read();

  sensors_event_t *event;
  accel.getEvent(event);
  StateInfo info = StateInfo {&pulse, &bmp, event};

  screen.run_app(&info);
  network.autoUpdateNTP();

  vTaskDelay(10);
  // Serial.print("Temperature = ");
  // Serial.print(bmp.readTemperature());
  // Serial.println(" *C");

  // Serial.print("X: ");
  // Serial.print(event.acceleration.x);
  // Serial.print("  ");
  // Serial.print("Y: ");
  // Serial.print(event.acceleration.y);
  // Serial.print("  ");
  // Serial.print("Z: ");
  // Serial.print(event.acceleration.z);
  // Serial.print("  ");
  // Serial.println("m/s^2 ");
  // Serial.print("Pressure = ");
  // Serial.print(bmp.readAltitude());
  // Serial.println(" Pa");

  // Serial.print("Altitude = ");
  // Serial.print(bmp.readAltitude());
  // Serial.println(" meters");

  // Serial.print("Pressure at sealevel (calculated) = ");
  // Serial.print(bmp.readSealevelPressure());
  // Serial.println(" Pa");

  // Serial.print("Real altitude = ");
  // Serial.print(bmp.readAltitude(102000));
  // Serial.println(" meters");

  // Serial.println();
  // delay(500);
}
