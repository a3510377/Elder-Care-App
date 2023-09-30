#pragma once

#include "../base.h"

class Home: public BaseApp {
 public:
  Home();

  void main_process();
  void update_clock();

  lv_obj_t *uiPower;
  lv_obj_t *uiTimeDate;
  lv_obj_t *uiTimeHour;
  lv_obj_t *uiTimeMinute;
  lv_obj_t *uiTimeSeconds;
  lv_obj_t *uiTimeSplit;
  lv_obj_t *uiHeart;
  lv_obj_t *uiHeartNum;
};
