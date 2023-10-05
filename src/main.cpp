#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <PulseSensor.h>
#include <SPIFFS.h>

#include "app/display.h"
#include "network.h"
#include "variable.h"

PulseSensor pulse(36, 21);
Adafruit_BMP085 bmp;
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

  if (!SPIFFS.begin(true)) {
    Serial.println(F("An error occurred while mounting SPIFFS"));

    return;
  }

  if (!bmp.begin()) {
    Serial.println(
        "Could not find a valid BMP085/BMP180 sensor, check wiring!");
    while (1) {
    }
  }

  analogReadResolution(10);

  network.init();
  pulse.begin();
  screen.init();
  screen.setup_app();

  xTaskCreatePinnedToCore(TaskTFT, "TaskTFT", 4096, NULL, 0, NULL, 1);
}

void loop() {
  screen.run_app();
  network.autoUpdateNTP();
  // pulse.read();
  delay(200);
  // Serial.print("Temperature = ");
  // Serial.print(bmp.readTemperature());
  // Serial.println(" *C");

  // Serial.print("Pressure = ");
  // Serial.print(bmp.readPressure());
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
