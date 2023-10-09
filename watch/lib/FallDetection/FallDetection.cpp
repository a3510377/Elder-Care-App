#include "FallDetection.h"

// Algorithm reference:
// https://maker.pro/arduino/tutorial/how-to-build-a-fall-detector-with-arduino

void FallDetection::loop(sensors_event_t event) {
  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;
  float totalAcceleration = sqrt(x * x + y * y + z * z);

  switch (_step) {
    // step0: check totalAcceleration > 25
    case 0: {
      if (totalAcceleration < 18) return;

      _next_step();
    } break;
    // step1: check whether the totalAcceleration breaks through the higher
    //        threshold within 500ms
    case 1: {
      if (millis() - _step_start_time > 500) {
        _step = 0;
        return;
      }

      if (totalAcceleration > 25) {
        _old_totalAcceleration = totalAcceleration;
        _next_step();
      }
    } break;
    // step2: Check whether the difference between the old and new data is
    // greater than the threshold. If it has not exceeded the threshold after
    // more than 1 second, trigger next
    case 2: {
      if (abs(_old_totalAcceleration - totalAcceleration) > 20) {
        _step = 0;
        return;
      }

      if (millis() - _step_start_time > 1e3) _next_step();
    } break;
    case 3: {
      _fall = true;
      _emit();
      return;
    }
  }
}

void FallDetection::_next_step() {
  _step++;
  _step_start_time = millis();
}

void FallDetection::_emit() {
  for (const auto &callback : _callbacks) {
    (*callback)(_fall);
  }
}
