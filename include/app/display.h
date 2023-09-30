#pragma once
#include "base.h"

void setup();

class Display {
 public:
  void init(void);
  void routine(void);
  void setBrightness(int value, int maxValue = 255);

  void kill_app();
  void setup_app();
  void run_app();

 private:
  uint8_t _now_app = 0;
  BaseApp *_app;
};
