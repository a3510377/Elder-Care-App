#pragma once

#include "../base.h"

static void screenLoadEvent(lv_event_t *);
static void moveXAnimation(lv_obj_t *, int32_t, int32_t);
static void moveYAnimation(lv_obj_t *, int32_t, int32_t);

class Home: public BaseApp {
 public:
  Home();

  void main_process();
  void update_clock();

  lv_obj_t *uiBatteryGroup, *uiBatteryIcon, *uiBatteryPercent;

  lv_obj_t *uiTime;
  lv_obj_t *uiDateGroup, *uiYear, *uiMonth, *uiDay, *uiDateSplit;
  lv_obj_t *uiHourGroup, *uiHour1, *uiHour2;
  lv_obj_t *uiMin;
  lv_obj_t *uiSecGroup, *uiSecValue, *uiSecSplit;
};
