#include "app/home/home.h"

#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <WiFi.h>

#define range(low, item, hi) max(low, min(item, hi))

Home::Home() {
  uiBatteryGroup = lv_obj_create(scr);
  lv_obj_set_size(uiBatteryGroup, 50, 20);
  lv_obj_set_pos(uiBatteryGroup, 0, -140);
  lv_obj_set_align(uiBatteryGroup, LV_ALIGN_CENTER);
  lv_obj_clear_flag(uiBatteryGroup, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(uiBatteryGroup, lv_color_hex(0xFFFFFF),
                            LV_CU_BASE_STYLE);
  lv_obj_set_style_bg_opa(uiBatteryGroup, 0, LV_CU_BASE_STYLE);
  lv_obj_set_style_border_color(uiBatteryGroup, lv_color_hex(0x000000),
                                LV_CU_BASE_STYLE);
  lv_obj_set_style_border_opa(uiBatteryGroup, 0, LV_CU_BASE_STYLE);

  uiBatteryIcon = lv_label_create(uiBatteryGroup);
  lv_obj_set_size(uiBatteryIcon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiBatteryIcon, -14, -3);
  lv_obj_set_align(uiBatteryIcon, LV_ALIGN_CENTER);
  lv_label_set_text(uiBatteryIcon, ICON_BOLT);
  lv_obj_set_style_text_color(uiBatteryIcon, lv_color_hex(0xFF0000),
                              LV_CU_BASE_STYLE);
  lv_obj_set_style_text_opa(uiBatteryIcon, 255, LV_CU_BASE_STYLE);
  lv_obj_set_style_text_font(uiBatteryIcon, &fontIcon, LV_CU_BASE_STYLE);

  uiBatteryPercent = lv_label_create(uiBatteryGroup);
  lv_obj_set_size(uiBatteryPercent, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiBatteryPercent, 10, -2);
  lv_obj_set_align(uiBatteryPercent, LV_ALIGN_CENTER);
  lv_label_set_text(uiBatteryPercent, "20%");
  lv_obj_set_style_text_color(uiBatteryPercent, lv_color_hex(0xFFFFFF),
                              LV_CU_BASE_STYLE);
  lv_obj_set_style_text_opa(uiBatteryPercent, 255, LV_CU_BASE_STYLE);

  uiTime = lv_obj_create(scr);
  lv_obj_set_size(uiTime, 240, 111);
  lv_obj_set_pos(uiTime, 1, -54);
  lv_obj_set_align(uiTime, LV_ALIGN_CENTER);
  lv_obj_clear_flag(uiTime, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(uiTime, lv_color_hex(0xFFFFFF), LV_CU_BASE_STYLE);
  lv_obj_set_style_bg_opa(uiTime, 0, LV_CU_BASE_STYLE);
  lv_obj_set_style_border_color(uiTime, lv_color_hex(0x000000),
                                LV_CU_BASE_STYLE);
  lv_obj_set_style_border_opa(uiTime, 0, LV_CU_BASE_STYLE);

  uiDateGroup = lv_obj_create(uiTime);
  lv_obj_set_size(uiDateGroup, 71, 43);
  lv_obj_set_pos(uiDateGroup, 41, -27);
  lv_obj_set_align(uiDateGroup, LV_ALIGN_CENTER);
  lv_obj_clear_flag(uiDateGroup, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(uiDateGroup, lv_color_hex(0xFFFFFF),
                            LV_CU_BASE_STYLE);
  lv_obj_set_style_bg_opa(uiDateGroup, 0, LV_CU_BASE_STYLE);
  lv_obj_set_style_border_color(uiDateGroup, lv_color_hex(0x000000),
                                LV_CU_BASE_STYLE);
  lv_obj_set_style_border_opa(uiDateGroup, 0, LV_CU_BASE_STYLE);

  uiYear = lv_label_create(uiDateGroup);
  lv_obj_set_size(uiYear, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiYear, -10, -13);
  lv_obj_set_align(uiYear, LV_ALIGN_CENTER);
  lv_label_set_text(uiYear, "2033");
  lv_obj_set_style_text_color(uiYear, lv_color_hex(0x808080), LV_CU_BASE_STYLE);
  lv_obj_set_style_text_opa(uiYear, 255, LV_CU_BASE_STYLE);
  lv_obj_set_style_text_font(uiYear, &lv_font_montserrat_18, LV_CU_BASE_STYLE);

  uiMonth = lv_label_create(uiDateGroup);
  lv_obj_set_size(uiMonth, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiMonth, -5, 8);
  lv_obj_set_align(uiMonth, LV_ALIGN_CENTER);
  lv_label_set_text(uiMonth, "02");
  lv_obj_set_style_text_font(uiMonth, &lv_font_montserrat_18, LV_CU_BASE_STYLE);

  uiDay = lv_label_create(uiDateGroup);
  lv_obj_set_size(uiDay, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiDay, 25, 8);
  lv_obj_set_align(uiDay, LV_ALIGN_CENTER);
  lv_label_set_text(uiDay, "30");
  lv_obj_set_style_text_font(uiDay, &lv_font_montserrat_18, LV_CU_BASE_STYLE);

  uiDateSplit = lv_label_create(uiDateGroup);
  lv_obj_set_size(uiDateSplit, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiDateSplit, 9, 6);
  lv_obj_set_align(uiDateSplit, LV_ALIGN_CENTER);
  lv_label_set_text(uiDateSplit, "-");
  lv_obj_set_style_text_font(uiDateSplit, &lv_font_montserrat_18,
                             LV_CU_BASE_STYLE);

  uiHourGroup = lv_obj_create(uiTime);
  lv_obj_set_size(uiHourGroup, 118, 75);
  lv_obj_set_pos(uiHourGroup, -64, -15);
  lv_obj_set_align(uiHourGroup, LV_ALIGN_CENTER);
  lv_obj_clear_flag(uiHourGroup, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(uiHourGroup, lv_color_hex(0xFFFFFF),
                            LV_CU_BASE_STYLE);
  lv_obj_set_style_bg_opa(uiHourGroup, 0, LV_CU_BASE_STYLE);
  lv_obj_set_style_border_color(uiHourGroup, lv_color_hex(0x000000),
                                LV_CU_BASE_STYLE);
  lv_obj_set_style_border_opa(uiHourGroup, 0, LV_CU_BASE_STYLE);

  uiHour1 = lv_label_create(uiHourGroup);
  lv_obj_set_size(uiHour1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiHour1, -25, 0);
  lv_obj_set_align(uiHour1, LV_ALIGN_CENTER);
  lv_label_set_text(uiHour1, "0");
  lv_obj_set_style_text_color(uiHour1, lv_color_hex(0x808080),
                              LV_CU_BASE_STYLE);
  lv_obj_set_style_text_opa(uiHour1, 255, LV_CU_BASE_STYLE);
  lv_obj_set_style_text_font(uiHour1, &fontNumberExtra, LV_CU_BASE_STYLE);

  uiHour2 = lv_label_create(uiHourGroup);
  lv_obj_set_size(uiHour2, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiHour2, 34, 0);
  lv_obj_set_align(uiHour2, LV_ALIGN_CENTER);
  lv_label_set_text(uiHour2, "3");
  lv_obj_set_style_text_font(uiHour2, &fontNumberExtra, LV_CU_BASE_STYLE);

  uiMin = lv_label_create(uiTime);
  lv_obj_set_size(uiMin, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiMin, 47, 22);
  lv_obj_set_align(uiMin, LV_ALIGN_CENTER);
  lv_label_set_text(uiMin, "20");
  lv_obj_set_style_text_color(uiMin, lv_color_hex(0x8880D5), LV_CU_BASE_STYLE);
  lv_obj_set_style_text_opa(uiMin, 255, LV_CU_BASE_STYLE);
  lv_obj_set_style_text_font(uiMin, &fontNumberBig, LV_CU_BASE_STYLE);

  uiSec = lv_label_create(scr);
  lv_obj_set_size(uiSec, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiSec, 100, 0);
  lv_obj_set_align(uiSec, LV_ALIGN_CENTER);
  lv_label_set_text(uiSec, "20");
  lv_obj_set_style_text_color(uiSec, lv_color_hex(0x9A9A9A), LV_CU_BASE_STYLE);
  lv_obj_set_style_text_opa(uiSec, 255, LV_CU_BASE_STYLE);
  lv_obj_set_style_text_font(uiSec, &lv_font_montserrat_16, LV_CU_BASE_STYLE);

  uiInfoGroup = lv_obj_create(scr);
  lv_obj_set_size(uiInfoGroup, 105, 89);
  lv_obj_set_pos(uiInfoGroup, -56, 98);
  lv_obj_set_align(uiInfoGroup, LV_ALIGN_CENTER);
  lv_obj_clear_flag(uiInfoGroup, LV_OBJ_FLAG_SCROLLABLE);

  uiTemperatureIcon = lv_label_create(uiInfoGroup);
  lv_obj_set_size(uiTemperatureIcon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiTemperatureIcon, -32, 25);
  lv_obj_set_align(uiTemperatureIcon, LV_ALIGN_CENTER);
  lv_label_set_text(uiTemperatureIcon, ICON_THERMOSTAT);
  lv_obj_set_style_text_font(uiTemperatureIcon, &fontIcon, LV_CU_BASE_STYLE);

  uiTemperatureValue = lv_label_create(uiInfoGroup);
  lv_obj_set_size(uiTemperatureValue, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiTemperatureValue, -20, 1);
  lv_obj_set_align(uiTemperatureValue, LV_ALIGN_CENTER);
  lv_label_set_text(uiTemperatureValue, "000");

  uiStepsIcon = lv_label_create(uiInfoGroup);
  lv_obj_set_size(uiStepsIcon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiStepsIcon, -32, 1);
  lv_obj_set_align(uiStepsIcon, LV_ALIGN_CENTER);
  lv_label_set_text(uiStepsIcon, ICON_FOOTPRINT);
  lv_obj_set_style_text_font(uiStepsIcon, &fontIcon, LV_CU_BASE_STYLE);

  uiStepsValue = lv_label_create(uiInfoGroup);
  lv_obj_set_size(uiStepsValue, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiStepsValue, -20, 1);
  lv_obj_set_align(uiStepsValue, LV_ALIGN_CENTER);
  lv_label_set_text(uiStepsValue, "000");

  uiAltitudeIcon = lv_label_create(uiInfoGroup);
  lv_obj_set_size(uiAltitudeIcon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiAltitudeIcon, -32, -27);
  lv_obj_set_align(uiAltitudeIcon, LV_ALIGN_CENTER);
  lv_label_set_text(uiAltitudeIcon, ICON_LANDSCAPE);
  lv_obj_set_style_text_font(uiAltitudeIcon, &fontIcon, LV_CU_BASE_STYLE);

  uiAltitudeValue = lv_label_create(uiInfoGroup);
  lv_obj_set_size(uiAltitudeValue, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiAltitudeValue, -20, -27);
  lv_obj_set_align(uiAltitudeValue, LV_ALIGN_CENTER);
  lv_label_set_text(uiAltitudeValue, "");

  uiWiFiStatusIcon = lv_label_create(scr);
  lv_obj_set_size(uiWiFiStatusIcon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiWiFiStatusIcon, 96, -144);
  lv_obj_set_align(uiWiFiStatusIcon, LV_ALIGN_CENTER);
  lv_label_set_text(uiWiFiStatusIcon, ICON_WIFI_FIND);
  lv_obj_set_style_text_font(uiWiFiStatusIcon, &fontIcon, LV_CU_BASE_STYLE);

  lv_obj_add_event_cb(scr, screenLoadEvent, LV_EVENT_SCREEN_LOADED, this);
}

static void screenLoadEvent(lv_event_t *e) {
  Home *home = (Home *)lv_event_get_user_data(e);

  //
  moveXAnimation(home->uiHourGroup, -100, 0);
  //
  moveXAnimation(home->uiDateGroup, 100, 0);
  moveXAnimation(home->uiSec, 100, 0);
  moveXAnimation(home->uiMin, 100, 0);
  //
  moveYAnimation(home->uiBatteryGroup, -100, 0);
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
  if (getLocalTime(&now)) {
    char buf[4];
    sprintf(buf, "%02d", range(0, now.tm_sec, 60));
    lv_label_set_text(uiSec, buf);

    sprintf(buf, "%ld", 1900L + now.tm_year);
    lv_label_set_text(uiYear, buf);

    sprintf(buf, "%02d", range(0, now.tm_mon, 11) + 1);
    lv_label_set_text(uiMonth, buf);

    sprintf(buf, "%02d", range(1, now.tm_mday, 31));
    lv_label_set_text(uiDay, buf);

    String hours = String(range(0, now.tm_hour, 23));
    lv_label_set_text(uiHour1,
                      hours.length() > 1 ? hours.substring(0, 1).c_str() : "0");
    lv_label_set_text(uiHour2, hours.substring(1, 2).c_str());

    sprintf(buf, "%02d", range(0, now.tm_min, 59));
    lv_label_set_text(uiMin, buf);
  }

  if (info != NULL) {
    Adafruit_BMP085 *bpm085 = info->bpm085;
    Serial.println(bpm085->readTemperature());

    // lv_label_set_text(uiTemperatureValue,
    //                   String(bpm085->readTemperature()).c_str());
  }
  lv_label_set_text(uiWiFiStatusIcon,
                    WiFi.isConnected() ? ICON_WIFI : ICON_WIFI_FIND);
}
