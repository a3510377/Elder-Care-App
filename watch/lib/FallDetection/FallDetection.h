#pragma once
#include <Adafruit_ADXL345_U.h>
#include <Arduino.h>
#include <StringArray.h>

typedef std::function<void(bool var)> FallDetectionFunction;

class FallDetection {
 public:
  FallDetection()
      : _callbacks(LinkedList<FallDetectionFunction *>(
            [](FallDetectionFunction *r) {})) {};

  void loop(sensors_event_t event);

  inline void close_fall(void) {
    _fall = false;
    _emit();
  }

  inline bool has_fall(void) {
    return _fall;
  }

 protected:
  LinkedList<FallDetectionFunction *> _callbacks;
  uint8_t _step;
  u_long _step_start_time;
  int _old_totalAcceleration;
  bool _fall;

  void _emit(void);
  void _next_step(void);
};
