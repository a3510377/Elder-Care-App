#pragma once
#include <Adafruit_ADXL345_U.h>
#include <Arduino.h>
#include <StringArray.h>

typedef std::function<void()> FallDetectionFunction;

class FallDetection {
 public:
  void loop(sensors_event_t event);

  inline ulong get_step_time() {
    return _step_start_time;
  }

  inline void close_warning(void) {
    _step = 0;
    _falling = false;
  }

  inline bool has_falling(void) {
    return _falling;
  }

  inline void set_handler(FallDetectionFunction handler) {
    _handler = handler;
  }

 protected:
  FallDetectionFunction _handler;

  uint8_t _step;
  u_long _step_start_time;
  int _old_totalAcceleration;
  bool _falling;

  void _next_step(void);
};
