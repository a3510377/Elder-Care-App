#include "FallDetection.h"

// Algorithm reference:
// https://maker.pro/arduino/tutorial/how-to-build-a-fall-detector-with-arduino

void FallDetection::loop(sensors_event_t event) {
  loop(sqrt(sq(event.acceleration.x) + sq(event.acceleration.y) +
            sq(event.acceleration.z)));
}

void FallDetection::loop(float total_acceleration) {
  switch (_step) {
    // step0: check totalAcceleration > 18
    case 0: {
      if (total_acceleration < 18) return;

      _next_step();
    } break;
    // step1: check whether the total_acceleration breaks through the higher
    //        threshold within 500ms
    case 1: {
      if (millis() - _step_start_time > 500) {
        _step = 0;
        return;
      }

      if (total_acceleration > 25) {
        _old_totalAcceleration = total_acceleration;
        _next_step();
      }
    } break;
    // step2: Check whether the difference between the old and new data is
    //        greater than the threshold. If it has not exceeded the threshold
    //        after more than 1 second, trigger next
    case 2: {
      if (abs(_old_totalAcceleration - total_acceleration) > 20) {
        _step = 0;
        return;
      }

      if (millis() - _step_start_time > 1e3) _next_step();
    } break;
    case 3: {
      _falling = true;

      if (millis() - _step_start_time > 5e3) {
        if (_handler != NULL) _handler();

        close_warning();
      }

    } break;
    default: {
      _step = 0;
    }
  }
}

void FallDetection::_next_step() {
  _step++;
  _step_start_time = millis();
}
