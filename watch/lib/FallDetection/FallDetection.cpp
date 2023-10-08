#include "FallDetection.h"

void FallDetection::loop(sensors_event_t event) {
  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;
  float totalAcceleration = sqrt(x * x + y * y + z * z);

  switch (_step) {}
}
