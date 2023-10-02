#include <Arduino.h>
#include <PulseSensor.h>
#include <SPIFFS.h>
#include <Wire.h>

#include "app/display.h"
#include "network.h"
#include "variable.h"

PulseSensor pulse(36, 21);
Display screen;
Network network;

SemaphoreHandle_t lvgl_mutex = xSemaphoreCreateMutex();

void TaskTFT(void *) {
  while (1) {
    xSemaphoreTake(lvgl_mutex, portMAX_DELAY);
    screen.run_app();
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

  analogReadResolution(10);
  network.init();

  pulse.begin();
  screen.init();
  screen.setup_app();

  xTaskCreatePinnedToCore(TaskTFT, "TaskTFT", 20480, NULL, 3, NULL, 1);
}

void loop() {
  // pulse.read();
  // delay(20);
}
