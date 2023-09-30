
#include "app/home/home.h"

#include <Arduino.h>
#include <lvgl.h>

Home::Home() {
  lv_obj_set_style_text_font(_scr, &lv_font_montserrat_8,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  // uiPower = lv_slider_create(_scr);
  // lv_obj_set_width(uiPower, 100);
  // lv_obj_set_height(uiPower, 5);
  // lv_obj_set_x(uiPower, 0);
  // lv_obj_set_y(uiPower, 22);
  // lv_obj_set_align(uiPower, LV_ALIGN_CENTER);

  up_display();
  // uiTimeDate = lv_label_create(_scr);
  // uiTimeHour = lv_label_create(_scr);
  // uiTimeMinute = lv_label_create(_scr);
  // uiTimeSeconds = lv_label_create(_scr);
  // uiTimeSplit = lv_label_create(_scr);
  // uiHeart = lv_img_create(_scr);
  // uiHeartNum = lv_label_create(_scr);
}

void Home::main_process() {
  Serial.println("test");
}
void Home::update_clock() {}
