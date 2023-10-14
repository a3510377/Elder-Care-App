#pragma once
#include <Adafruit_ADXL345_U.h>
#include <Arduino.h>

#define STEP_COUNT_FILE_PATH "/step_count"

class StepCount {
 public:
  void init(void);
  void loop(sensors_event_t event);
  void loop(float total_acceleration);

  bool update_cache(void);

  inline uint get_step() {
    return _steps;
  }

 protected:
  uint _steps;
  float _old_total_acceleration;
  uint8_t _threshold = 6;
  bool _flag, _start;
};
