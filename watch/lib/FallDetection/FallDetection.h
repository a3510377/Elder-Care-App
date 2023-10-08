#pragma once
#include <Adafruit_ADXL345_U.h>
#include <Arduino.h>

class FallDetection {
 public:
  FallDetection(uint8_t threshold) : _threshold(threshold) {}

  void loop(sensors_event_t event);

 protected:
  uint8_t _step;
  uint8_t _thresholdSetting, _threshold;
};
