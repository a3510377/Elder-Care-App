#pragma once

#include <TFT_eSPI.h>

#include "ui.h"

#define LV_CU_BASE_STYLE LV_PART_MAIN | LV_STATE_DEFAULT

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

  virtual void main_process(void) {}  // virtual

  lv_obj_t *scr;
};
