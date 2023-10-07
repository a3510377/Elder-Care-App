#include "app/home/home.h"

#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <WiFi.h>

#define range(low, item, hi) max(low, min(item, hi))

Home::Home() {
  ui_batteryGroup = lv_obj_create(scr);
  lv_obj_set_size(ui_batteryGroup, 50, 20);
  lv_obj_set_pos(ui_batteryGroup, 0, -140);
  lv_obj_set_align(ui_batteryGroup, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_batteryGroup, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(ui_batteryGroup, lv_color_hex(0xFFFFFF),
                            LV_CU_BASE_STYLE);
  lv_obj_set_style_bg_opa(ui_batteryGroup, 0, LV_CU_BASE_STYLE);
  lv_obj_set_style_border_color(ui_batteryGroup, lv_color_hex(0x000000),
                                LV_CU_BASE_STYLE);
  lv_obj_set_style_border_opa(ui_batteryGroup, 0, LV_CU_BASE_STYLE);

  ui_batteryIcon = lv_label_create(ui_batteryGroup);
  lv_obj_set_size(ui_batteryIcon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_batteryIcon, -14, -3);
  lv_obj_set_align(ui_batteryIcon, LV_ALIGN_CENTER);
  lv_label_set_text(ui_batteryIcon, ICON_BOLT);
  lv_obj_set_style_text_color(ui_batteryIcon, lv_color_hex(0xFF0000),
                              LV_CU_BASE_STYLE);
  lv_obj_set_style_text_opa(ui_batteryIcon, 255, LV_CU_BASE_STYLE);
  lv_obj_set_style_text_font(ui_batteryIcon, &fontIcon, LV_CU_BASE_STYLE);

  ui_batteryPercent = lv_label_create(ui_batteryGroup);
  lv_obj_set_size(ui_batteryPercent, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_batteryPercent, 10, -2);
  lv_obj_set_align(ui_batteryPercent, LV_ALIGN_CENTER);
  lv_label_set_text(ui_batteryPercent, "20%");
  lv_obj_set_style_text_color(ui_batteryPercent, lv_color_hex(0xFFFFFF),
                              LV_CU_BASE_STYLE);
  lv_obj_set_style_text_opa(ui_batteryPercent, 255, LV_CU_BASE_STYLE);

  ui_time = lv_obj_create(scr);
  lv_obj_set_size(ui_time, 240, 111);
  lv_obj_set_pos(ui_time, 1, -54);
  lv_obj_set_align(ui_time, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_time, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(ui_time, lv_color_hex(0xFFFFFF), LV_CU_BASE_STYLE);
  lv_obj_set_style_bg_opa(ui_time, 0, LV_CU_BASE_STYLE);
  lv_obj_set_style_border_color(ui_time, lv_color_hex(0x000000),
                                LV_CU_BASE_STYLE);
  lv_obj_set_style_border_opa(ui_time, 0, LV_CU_BASE_STYLE);

  ui_dateGroup = lv_obj_create(ui_time);
  lv_obj_set_size(ui_dateGroup, 71, 43);
  lv_obj_set_pos(ui_dateGroup, 41, -27);
  lv_obj_set_align(ui_dateGroup, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_dateGroup, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(ui_dateGroup, lv_color_hex(0xFFFFFF),
                            LV_CU_BASE_STYLE);
  lv_obj_set_style_bg_opa(ui_dateGroup, 0, LV_CU_BASE_STYLE);
  lv_obj_set_style_border_color(ui_dateGroup, lv_color_hex(0x000000),
                                LV_CU_BASE_STYLE);
  lv_obj_set_style_border_opa(ui_dateGroup, 0, LV_CU_BASE_STYLE);

  ui_year = lv_label_create(ui_dateGroup);
  lv_obj_set_size(ui_year, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_year, -10, -13);
  lv_obj_set_align(ui_year, LV_ALIGN_CENTER);
  lv_label_set_text(ui_year, "2033");
  lv_obj_set_style_text_color(ui_year, lv_color_hex(0x808080),
                              LV_CU_BASE_STYLE);
  lv_obj_set_style_text_opa(ui_year, 255, LV_CU_BASE_STYLE);
  lv_obj_set_style_text_font(ui_year, &lv_font_montserrat_18, LV_CU_BASE_STYLE);

  ui_month = lv_label_create(ui_dateGroup);
  lv_obj_set_size(ui_month, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_month, -5, 8);
  lv_obj_set_align(ui_month, LV_ALIGN_CENTER);
  lv_label_set_text(ui_month, "02");
  lv_obj_set_style_text_font(ui_month, &lv_font_montserrat_18,
                             LV_CU_BASE_STYLE);

  ui_day = lv_label_create(ui_dateGroup);
  lv_obj_set_size(ui_day, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_day, 25, 8);
  lv_obj_set_align(ui_day, LV_ALIGN_CENTER);
  lv_label_set_text(ui_day, "30");
  lv_obj_set_style_text_font(ui_day, &lv_font_montserrat_18, LV_CU_BASE_STYLE);

  ui_dateSplit = lv_label_create(ui_dateGroup);
  lv_obj_set_size(ui_dateSplit, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_dateSplit, 9, 6);
  lv_obj_set_align(ui_dateSplit, LV_ALIGN_CENTER);
  lv_label_set_text(ui_dateSplit, "-");
  lv_obj_set_style_text_font(ui_dateSplit, &lv_font_montserrat_18,
                             LV_CU_BASE_STYLE);

  ui_hourGroup = lv_obj_create(ui_time);
  lv_obj_set_size(ui_hourGroup, 118, 75);
  lv_obj_set_pos(ui_hourGroup, -64, -15);
  lv_obj_set_align(ui_hourGroup, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_hourGroup, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(ui_hourGroup, lv_color_hex(0xFFFFFF),
                            LV_CU_BASE_STYLE);
  lv_obj_set_style_bg_opa(ui_hourGroup, 0, LV_CU_BASE_STYLE);
  lv_obj_set_style_border_color(ui_hourGroup, lv_color_hex(0x000000),
                                LV_CU_BASE_STYLE);
  lv_obj_set_style_border_opa(ui_hourGroup, 0, LV_CU_BASE_STYLE);

  ui_hour1 = lv_label_create(ui_hourGroup);
  lv_obj_set_size(ui_hour1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_hour1, -25, 0);
  lv_obj_set_align(ui_hour1, LV_ALIGN_CENTER);
  lv_label_set_text(ui_hour1, "0");
  lv_obj_set_style_text_color(ui_hour1, lv_color_hex(0x808080),
                              LV_CU_BASE_STYLE);
  lv_obj_set_style_text_opa(ui_hour1, 255, LV_CU_BASE_STYLE);
  lv_obj_set_style_text_font(ui_hour1, &fontNumberExtra, LV_CU_BASE_STYLE);

  ui_hour2 = lv_label_create(ui_hourGroup);
  lv_obj_set_size(ui_hour2, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_hour2, 34, 0);
  lv_obj_set_align(ui_hour2, LV_ALIGN_CENTER);
  lv_label_set_text(ui_hour2, "3");
  lv_obj_set_style_text_font(ui_hour2, &fontNumberExtra, LV_CU_BASE_STYLE);

  ui_min = lv_label_create(ui_time);
  lv_obj_set_size(ui_min, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_min, 47, 22);
  lv_obj_set_align(ui_min, LV_ALIGN_CENTER);
  lv_label_set_text(ui_min, "20");
  lv_obj_set_style_text_color(ui_min, lv_color_hex(0x8880D5), LV_CU_BASE_STYLE);
  lv_obj_set_style_text_opa(ui_min, 255, LV_CU_BASE_STYLE);
  lv_obj_set_style_text_font(ui_min, &fontNumberBig, LV_CU_BASE_STYLE);

  ui_secGroup = lv_obj_create(ui_time);
  lv_obj_set_size(ui_secGroup, 27, 15);
  lv_obj_set_pos(ui_secGroup, 99, 41);
  lv_obj_set_align(ui_secGroup, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_secGroup, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(ui_secGroup, lv_color_hex(0xFFFFFF),
                            LV_CU_BASE_STYLE);
  lv_obj_set_style_bg_opa(ui_secGroup, 0, LV_CU_BASE_STYLE);
  lv_obj_set_style_border_color(ui_secGroup, lv_color_hex(0x000000),
                                LV_CU_BASE_STYLE);
  lv_obj_set_style_border_opa(ui_secGroup, 0, LV_CU_BASE_STYLE);

  ui_secValue = lv_label_create(ui_secGroup);
  lv_obj_set_size(ui_secValue, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_secValue, 4, 0);
  lv_obj_set_align(ui_secValue, LV_ALIGN_CENTER);
  lv_label_set_text(ui_secValue, "20");
  lv_obj_set_style_text_color(ui_secValue, lv_color_hex(0x9A9A9A),
                              LV_CU_BASE_STYLE);
  lv_obj_set_style_text_opa(ui_secValue, 255, LV_CU_BASE_STYLE);
  lv_obj_set_style_text_font(ui_secValue, &lv_font_montserrat_16,
                             LV_CU_BASE_STYLE);

  ui_secSplit = lv_label_create(ui_secGroup);
  lv_obj_set_size(ui_secSplit, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_secSplit, -11, -1);
  lv_obj_set_align(ui_secSplit, LV_ALIGN_CENTER);
  lv_label_set_text(ui_secSplit, ":");
  lv_obj_set_style_text_color(ui_secSplit, lv_color_hex(0x808080),
                              LV_CU_BASE_STYLE);
  lv_obj_set_style_text_opa(ui_secSplit, 255, LV_CU_BASE_STYLE);
  lv_obj_set_style_text_font(ui_secSplit, &lv_font_montserrat_16,
                             LV_CU_BASE_STYLE);

  ui_Info = lv_obj_create(scr);
  lv_obj_set_size(ui_Info, 87, 89);
  lv_obj_set_pos(ui_Info, -61, 103);
  lv_obj_set_align(ui_Info, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_Info, LV_OBJ_FLAG_SCROLLABLE);

  ui_altitudeGroup = lv_obj_create(ui_Info);
  lv_obj_set_size(ui_altitudeGroup, 75, 22);
  lv_obj_set_pos(ui_altitudeGroup, 0, -29);
  lv_obj_set_align(ui_altitudeGroup, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_altitudeGroup, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_border_color(ui_altitudeGroup, lv_color_hex(0x000000),
                                LV_CU_BASE_STYLE);
  lv_obj_set_style_border_opa(ui_altitudeGroup, 0, LV_CU_BASE_STYLE);

  ui_altitudeIcon = lv_label_create(ui_altitudeGroup);
  lv_obj_set_size(ui_altitudeIcon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_altitudeIcon, -27, 1);
  lv_obj_set_align(ui_altitudeIcon, LV_ALIGN_CENTER);
  lv_label_set_text(ui_altitudeIcon, ICON_HEART);
  lv_obj_set_style_text_font(ui_altitudeIcon, &fontIcon, LV_CU_BASE_STYLE);

  ui_altitudeValue = lv_label_create(ui_altitudeGroup);
  lv_obj_set_size(ui_altitudeValue, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_altitudeValue, 10, 1);
  lv_obj_set_align(ui_altitudeValue, LV_ALIGN_RIGHT_MID);
  lv_label_set_text(ui_altitudeValue, "0");

  ui_stepsGroup = lv_obj_create(ui_Info);
  lv_obj_set_size(ui_stepsGroup, 75, 22);
  lv_obj_set_align(ui_stepsGroup, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_stepsGroup, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(ui_stepsGroup, lv_color_hex(0xFFFFFF),
                            LV_CU_BASE_STYLE);
  lv_obj_set_style_bg_opa(ui_stepsGroup, 0, LV_CU_BASE_STYLE);
  lv_obj_set_style_border_color(ui_stepsGroup, lv_color_hex(0x000000),
                                LV_CU_BASE_STYLE);
  lv_obj_set_style_border_opa(ui_stepsGroup, 0, LV_CU_BASE_STYLE);

  ui_stepsIcon = lv_label_create(ui_stepsGroup);
  lv_obj_set_size(ui_stepsIcon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_stepsIcon, -27, 1);
  lv_obj_set_align(ui_stepsIcon, LV_ALIGN_CENTER);
  lv_label_set_text(ui_stepsIcon, ICON_FOOTPRINT);
  lv_obj_set_style_text_font(ui_stepsIcon, &fontIcon, LV_CU_BASE_STYLE);

  ui_stepsValue = lv_label_create(ui_stepsGroup);
  lv_obj_set_size(ui_stepsValue, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_stepsValue, 10, 1);
  lv_obj_set_align(ui_stepsValue, LV_ALIGN_RIGHT_MID);
  lv_label_set_text(ui_stepsValue, "0");

  ui_temperatureGroup = lv_obj_create(ui_Info);
  lv_obj_set_size(ui_temperatureGroup, 75, 22);
  lv_obj_set_pos(ui_temperatureGroup, 0, 29);
  lv_obj_set_align(ui_temperatureGroup, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_temperatureGroup, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(ui_temperatureGroup, lv_color_hex(0xFFFFFF),
                            LV_CU_BASE_STYLE);
  lv_obj_set_style_bg_opa(ui_temperatureGroup, 0, LV_CU_BASE_STYLE);
  lv_obj_set_style_border_color(ui_temperatureGroup, lv_color_hex(0x000000),
                                LV_CU_BASE_STYLE);
  lv_obj_set_style_border_opa(ui_temperatureGroup, 0, LV_CU_BASE_STYLE);

  ui_temperatureIcon = lv_label_create(ui_temperatureGroup);
  lv_obj_set_size(ui_temperatureIcon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_temperatureIcon, -27, 0);
  lv_obj_set_align(ui_temperatureIcon, LV_ALIGN_CENTER);
  lv_label_set_text(ui_temperatureIcon, ICON_THERMOSTAT);
  lv_obj_set_style_text_font(ui_temperatureIcon, &fontIcon, LV_CU_BASE_STYLE);

  ui_temperatureValue = lv_label_create(ui_temperatureGroup);
  lv_obj_set_size(ui_temperatureValue, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_temperatureValue, 3, 1);
  lv_obj_set_align(ui_temperatureValue, LV_ALIGN_CENTER);
  lv_label_set_text(ui_temperatureValue, "20");

  ui_temperatureUnit = lv_label_create(ui_temperatureGroup);
  lv_obj_set_size(ui_temperatureUnit, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_temperatureUnit, 26, 1);
  lv_obj_set_align(ui_temperatureUnit, LV_ALIGN_CENTER);
  lv_label_set_text(ui_temperatureUnit, "°C");

  ui_WiFiStatusIcon = lv_label_create(scr);
  lv_obj_set_size(ui_WiFiStatusIcon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(ui_WiFiStatusIcon, 96, -144);
  lv_obj_set_align(ui_WiFiStatusIcon, LV_ALIGN_CENTER);
  lv_label_set_text(ui_WiFiStatusIcon, ICON_WIFI_FIND);
  lv_obj_set_style_text_font(ui_WiFiStatusIcon, &fontIcon, LV_CU_BASE_STYLE);

  lv_obj_add_event_cb(scr, screenLoadEvent, LV_EVENT_SCREEN_LOADED, this);
}

static void screenLoadEvent(lv_event_t *e) {
  Home *home = (Home *)lv_event_get_user_data(e);

  //
  moveXAnimation(home->ui_hourGroup, -100, 0);
  //
  moveXAnimation(home->ui_dateGroup, 100, 0);
  moveXAnimation(home->ui_secGroup, 100, 0);
  moveXAnimation(home->ui_min, 100, 0);
  //
  moveYAnimation(home->ui_batteryGroup, -100, 0);
}

static void moveXAnimation(lv_obj_t *obj, int32_t start, int32_t end) {
  lv_anim_t animation;
  lv_anim_init(&animation);
  lv_anim_set_var(&animation, obj);
  lv_anim_set_time(&animation, 500);
  lv_anim_set_values(&animation, start, end);
  lv_anim_set_exec_cb(&animation, animCallbackSetX);
  lv_anim_set_path_cb(&animation, lv_anim_path_overshoot);
  lv_anim_set_get_value_cb(&animation, &animCallbackGetX);
  lv_anim_start(&animation);
}
static void moveYAnimation(lv_obj_t *obj, int32_t start, int32_t end) {
  lv_anim_t animation;
  lv_anim_init(&animation);
  lv_anim_set_var(&animation, obj);
  lv_anim_set_time(&animation, 500);
  lv_anim_set_values(&animation, start, end);
  lv_anim_set_exec_cb(&animation, animCallbackSetY);
  lv_anim_set_path_cb(&animation, lv_anim_path_overshoot);
  lv_anim_set_get_value_cb(&animation, &animCallbackGetY);
  lv_anim_start(&animation);
}

void Home::main_process(StateInfo *info) {
  struct tm now;
  char buf[4];
  if (getLocalTime(&now)) {
    sprintf(buf, "%02d", range(0, now.tm_sec, 60));
    lv_label_set_text(ui_secValue, buf);

    sprintf(buf, "%ld", 1900L + now.tm_year);
    lv_label_set_text(ui_year, buf);

    sprintf(buf, "%02d", range(0, now.tm_mon, 11) + 1);
    lv_label_set_text(ui_month, buf);

    sprintf(buf, "%02d", range(1, now.tm_mday, 31));
    lv_label_set_text(ui_day, buf);

    String hours = String(range(0, now.tm_hour, 23));
    lv_label_set_text(ui_hour1,
                      hours.length() > 1 ? hours.substring(0, 1).c_str() : "0");
    lv_label_set_text(ui_hour2, hours.substring(1, 2).c_str());

    sprintf(buf, "%02d", range(0, now.tm_min, 59));
    lv_label_set_text(ui_min, buf);
  }

  if (info != NULL) {
    sprintf(buf, "%02.1f", info->bpm085.readTemperature());
    lv_label_set_text(ui_temperatureValue, buf);
  }
  lv_label_set_text(ui_WiFiStatusIcon,
                    WiFi.isConnected() ? ICON_WIFI : ICON_WIFI_FIND);
}
