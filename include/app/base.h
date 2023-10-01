#pragma once

#include <TFT_eSPI.h>
#include <lvgl.h>

#include "ui.h"

#define LV_CU_BASE_STYLE LV_PART_MAIN | LV_STATE_DEFAULT

class BaseApp {
 public:
  BaseApp() {
    _scr = lv_obj_create(NULL);
    lv_obj_set_size(_scr, TFT_WIDTH, TFT_HEIGHT);
    lv_scr_load(_scr);
  }

  ~BaseApp() {
    lv_obj_del(_scr);
  }

  virtual void main_process(void) {}  // virtual

  inline void up_display(void) {
    lv_timer_handler();
  }

 protected:
  lv_obj_t *_scr;
};
