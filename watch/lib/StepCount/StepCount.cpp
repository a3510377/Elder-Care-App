#include "StepCount.h"

#include <SPIFFS.h>

void StepCount::init() {
  if (SPIFFS.exists(STEP_COUNT_FILE_PATH)) {
    File configFile = SPIFFS.open(STEP_COUNT_FILE_PATH, FILE_READ);
    while (configFile.available()) {
      String line = configFile.readStringUntil('\n');
      int separatorIndex = line.indexOf(':');

      if (separatorIndex != -1) {
        String key = line.substring(0, separatorIndex);

        struct tm now;
        char buf[10];  // 4+1+2+1+2 => 10
        if (getLocalTime(&now)) {
          strftime(buf, 10, "%Y/%m/%d", &now);

          if (key.equals(buf)) {
            String value = line.substring(separatorIndex + 1);
            _steps = value.toInt();
            _start = true;
            break;
          }
        }
      }
    }
  }
}

void StepCount::loop(sensors_event_t event) {
  loop(sqrt(sq(event.acceleration.x) + sq(event.acceleration.y) +
            sq(event.acceleration.z)));
}

void StepCount::loop(float total_acceleration) {
  if (!_start) init();

  float value = (total_acceleration + _old_total_acceleration) / 2;
  _old_total_acceleration = total_acceleration;

  if (value > _threshold && !_flag) {
    _steps++;
    _flag = true;
    update_cache();
  } else if (value < _threshold && _flag) _flag = false;
}

bool StepCount::update_cache() {
  File cacheFile = SPIFFS.open(STEP_COUNT_FILE_PATH, FILE_WRITE);
  struct tm now;

  if (!cacheFile || !getLocalTime(&now)) return false;

  char buf[10];  // 4+1+2+1+2
  strftime(buf, 10, "%Y/%m/%d", &now);

  cacheFile.print(buf);
  cacheFile.print(":");
  cacheFile.println(String(_steps));
  cacheFile.close();

  return true;
}
