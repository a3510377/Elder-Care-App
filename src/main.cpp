#include <Arduino.h>
#include <PulseSensor.h>
#include <Wire.h>

#include "app/display.h"
#include "variable.h"

PulseSensor pulse(36, 21);
Display screen;

void setup() {
  Serial.begin(9600);
  analogReadResolution(10);
  pulse.begin();
  screen.init();
  screen.setup_app();
}

void loop() {
  pulse.read();
  screen.run_app();
  delay(20);
}
