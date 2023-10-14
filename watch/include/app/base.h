#pragma once

#include <Adafruit_ADXL345_U.h>
#include <Adafruit_BMP085.h>
#include <FallDetection.h>
#include <PulseSensor.h>
#include <StepCount.h>
#include <TFT_eSPI.h>

#include "ui.h"

#define LV_CU_BASE_STYLE LV_PART_MAIN | LV_STATE_DEFAULT

struct StateInfo {
  PulseSensor pulse;
  Adafruit_BMP085 bpm085;
  FallDetection fallDetection;
  StepCount stepCount;
  sensors_event_t accel;
};

class BaseApp {
 public:
  BaseApp() {
    scr = lv_obj_create(NULL);
    lv_obj_set_size(scr, TFT_WIDTH, TFT_HEIGHT);
    lv_scr_load(scr);
  }

  ~BaseApp() {
    lv_obj_del(scr);
  }

  virtual void main_process(StateInfo *info) {}  // virtual

  lv_obj_t *scr;
};
