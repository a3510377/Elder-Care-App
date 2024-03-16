#pragma once

#include "../base.h"

static void screenLoadEvent(lv_event_t *);
static void moveXAnimation(lv_obj_t *, int32_t, int32_t);
static void moveYAnimation(lv_obj_t *, int32_t, int32_t);

class Home: public BaseApp {
 public:
  Home();

  void main_process(StateInfo *info);

  lv_obj_t *ui_batteryGroup;
  lv_obj_t *ui_batteryIcon;
  lv_obj_t *ui_batteryPercent;

  lv_obj_t *ui_time;
  lv_obj_t *ui_dateGroup;
  lv_obj_t *ui_year;
  lv_obj_t *ui_month;
  lv_obj_t *ui_day;
  lv_obj_t *ui_dateSplit;

  lv_obj_t *ui_hourGroup;
  lv_obj_t *ui_hour1;
  lv_obj_t *ui_hour2;

  lv_obj_t *ui_min;

  lv_obj_t *ui_secGroup;
  lv_obj_t *ui_secValue;
  lv_obj_t *ui_secSplit;

  lv_obj_t *ui_Info;
  lv_obj_t *ui_heartGroup;
  lv_obj_t *ui_heartIcon;
  lv_obj_t *ui_heartValue;

  lv_obj_t *ui_stepsGroup;
  lv_obj_t *ui_stepsIcon;
  lv_obj_t *ui_stepsValue;

  lv_obj_t *ui_temperatureGroup;
  lv_obj_t *ui_temperatureIcon;
  lv_obj_t *ui_temperatureValue;
  lv_obj_t *ui_temperatureUnit;

  lv_obj_t *ui_WiFiStatusIcon;

  lv_obj_t *ui_fallWarnGroup;
  lv_obj_t *ui_fallWarn;
};
