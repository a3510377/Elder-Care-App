#pragma once
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_BMP085.h>
#include <PulseSensor.h>

#include "base.h"

class Display {
 public:
  void init(void);
  void routine(void);
  void setBrightness(int value, int maxValue = 255);

  void kill_app();
  void setup_app();
  void run_app(StateInfo *info);

 private:
  uint8_t _now_app = 0;
  BaseApp *_app;
};
