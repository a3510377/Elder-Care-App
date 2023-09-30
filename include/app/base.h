#pragma once

#include <TFT_eSPI.h>
#include <lvgl.h>

class BaseApp {
 public:
  BaseApp() {
    _scr = lv_obj_create(NULL);
    // (scr, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,
    //                                 LV_COLOR_BLACK);
    lv_obj_set_size(_scr, TFT_WIDTH, TFT_HEIGHT);
    lv_scr_load(_scr);
  }

  ~BaseApp() {
    lv_obj_del(_scr);
  }

  virtual void main_process(void) {}  // virtual

  inline void up_display(void) {
    lv_task_handler();
  }

 protected:
  lv_obj_t *_scr;
};
