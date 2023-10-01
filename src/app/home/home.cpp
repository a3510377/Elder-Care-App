#include "app/home/home.h"

#include <Arduino.h>

Home::Home() {
  lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);

  {  // battery
    uiBatteryGroup = lv_obj_create(scr);
    lv_obj_set_size(uiBatteryGroup, 50, 20);
    lv_obj_set_pos(uiBatteryGroup, 0, -96);
    lv_obj_set_align(uiBatteryGroup, LV_ALIGN_CENTER);
    lv_obj_clear_flag(uiBatteryGroup, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(uiBatteryGroup, 0, LV_CU_BASE_STYLE);
    lv_obj_set_style_border_color(uiBatteryGroup, lv_color_hex(0x000000),
                                  LV_CU_BASE_STYLE);
    lv_obj_set_style_border_opa(uiBatteryGroup, 0, LV_CU_BASE_STYLE);

    uiBatteryIcon = lv_img_create(uiBatteryGroup);
    lv_img_set_src(uiBatteryIcon, &imageBattery);
    lv_obj_set_size(uiBatteryIcon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiBatteryIcon, -14, 0);
    lv_obj_set_align(uiBatteryIcon, LV_ALIGN_CENTER);
    lv_obj_add_flag(uiBatteryIcon, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(uiBatteryIcon, LV_OBJ_FLAG_SCROLLABLE);

    uiBatteryPercent = lv_label_create(uiBatteryGroup);
    lv_obj_set_size(uiBatteryPercent, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiBatteryPercent, 10, 0);
    lv_obj_set_align(uiBatteryPercent, LV_ALIGN_CENTER);
    lv_label_set_text(uiBatteryPercent, "--%");
    lv_obj_set_style_text_color(uiBatteryPercent, lv_color_hex(0xFFFFFF),
                                LV_CU_BASE_STYLE);
    lv_obj_set_style_text_opa(uiBatteryPercent, 255, LV_CU_BASE_STYLE);
  }

  uiTime = lv_obj_create(scr);
  lv_obj_set_size(uiTime, 240, 105);
  lv_obj_set_pos(uiTime, 0, -24);
  lv_obj_set_align(uiTime, LV_ALIGN_CENTER);
  lv_obj_clear_flag(uiTime, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_opa(uiTime, 0, LV_CU_BASE_STYLE);
  lv_obj_set_style_border_color(uiTime, lv_color_hex(0x000000),
                                LV_CU_BASE_STYLE);
  lv_obj_set_style_border_opa(uiTime, 0, LV_CU_BASE_STYLE);

  {  // date
    uiDateGroup = lv_obj_create(uiTime);
    lv_obj_set_size(uiDateGroup, 79, 43);
    lv_obj_set_pos(uiDateGroup, 33, -25);
    lv_obj_set_align(uiDateGroup, LV_ALIGN_CENTER);
    lv_obj_clear_flag(uiDateGroup, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(uiDateGroup, 0, LV_CU_BASE_STYLE);
    lv_obj_set_style_border_color(uiDateGroup, lv_color_hex(0x000000),
                                  LV_CU_BASE_STYLE);
    lv_obj_set_style_border_opa(uiDateGroup, 0, LV_CU_BASE_STYLE);

    uiYear = lv_label_create(uiDateGroup);
    lv_obj_set_size(uiYear, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiYear, -12, -13);
    lv_obj_set_align(uiYear, LV_ALIGN_CENTER);
    lv_label_set_text(uiYear, "2023");
    lv_obj_set_style_text_color(uiYear, lv_color_hex(0x808080),
                                LV_CU_BASE_STYLE);
    lv_obj_set_style_text_opa(uiYear, 255, LV_CU_BASE_STYLE);
    lv_obj_set_style_text_font(uiYear, &lv_font_montserrat_18,
                               LV_CU_BASE_STYLE);

    uiMonth = lv_label_create(uiDateGroup);
    lv_obj_set_size(uiMonth, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiMonth, -5, 8);
    lv_obj_set_align(uiMonth, LV_ALIGN_CENTER);
    lv_label_set_text(uiMonth, "00");
    lv_obj_set_style_text_font(uiMonth, &lv_font_montserrat_18,
                               LV_CU_BASE_STYLE);

    uiDay = lv_label_create(uiDateGroup);
    lv_obj_set_size(uiDay, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiDay, 26, 8);
    lv_obj_set_align(uiDay, LV_ALIGN_CENTER);
    lv_label_set_text(uiDay, "00");
    lv_obj_set_style_text_font(uiDay, &lv_font_montserrat_18, LV_CU_BASE_STYLE);

    uiDateSplit = lv_label_create(uiDateGroup);
    lv_obj_set_size(uiDateSplit, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiDateSplit, 10, 6);
    lv_obj_set_align(uiDateSplit, LV_ALIGN_CENTER);
    lv_label_set_text(uiDateSplit, "-");
    lv_obj_set_style_text_font(uiDateSplit, &lv_font_montserrat_18,
                               LV_CU_BASE_STYLE);
  }
  {
    uiHourGroup = lv_obj_create(uiTime);
    lv_obj_set_size(uiHourGroup, 118, 75);
    lv_obj_set_pos(uiHourGroup, -64, -15);
    lv_obj_set_align(uiHourGroup, LV_ALIGN_CENTER);
    lv_obj_clear_flag(uiHourGroup, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(uiHourGroup, 0, LV_CU_BASE_STYLE);
    lv_obj_set_style_border_color(uiHourGroup, lv_color_hex(0x000000),
                                  LV_CU_BASE_STYLE);
    lv_obj_set_style_border_opa(uiHourGroup, 0, LV_CU_BASE_STYLE);

    uiHour1 = lv_label_create(uiHourGroup);
    lv_obj_set_size(uiHour1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiHour1, -30, 0);
    lv_obj_set_align(uiHour1, LV_ALIGN_CENTER);
    lv_label_set_text(uiHour1, "0");
    lv_obj_set_style_text_color(uiHour1, lv_color_hex(0x808080),
                                LV_CU_BASE_STYLE);
    lv_obj_set_style_text_font(uiHour1, &fontNumberExtra, LV_CU_BASE_STYLE);

    uiHour2 = lv_label_create(uiHourGroup);
    lv_obj_set_size(uiHour2, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiHour2, 31, 0);
    lv_obj_set_align(uiHour2, LV_ALIGN_CENTER);
    lv_label_set_text(uiHour2, "0");
    lv_obj_set_style_text_font(uiHour2, &fontNumberExtra, LV_CU_BASE_STYLE);
  }

  uiMin = lv_label_create(uiTime);
  lv_obj_set_size(uiMin, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_pos(uiMin, 39, 25);
  lv_obj_set_align(uiMin, LV_ALIGN_CENTER);
  lv_label_set_text(uiMin, "00");
  lv_obj_set_style_text_color(uiMin, lv_color_hex(0x8880D5), LV_CU_BASE_STYLE);
  lv_obj_set_style_text_font(uiMin, &fontNumberBig, LV_CU_BASE_STYLE);

  {
    uiSecGroup = lv_obj_create(uiTime);
    lv_obj_set_size(uiSecGroup, 27, 15);
    lv_obj_set_pos(uiSecGroup, 92, 41);
    lv_obj_set_align(uiSecGroup, LV_ALIGN_CENTER);
    lv_obj_clear_flag(uiSecGroup, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(uiSecGroup, 0, LV_CU_BASE_STYLE);
    lv_obj_set_style_border_color(uiSecGroup, lv_color_hex(0x000000),
                                  LV_CU_BASE_STYLE);
    lv_obj_set_style_border_opa(uiSecGroup, 0, LV_CU_BASE_STYLE);

    uiSecSplit = lv_label_create(uiSecGroup);
    lv_obj_set_size(uiSecSplit, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiSecSplit, -9, 0);
    lv_obj_set_align(uiSecSplit, LV_ALIGN_CENTER);
    lv_label_set_text(uiSecSplit, ":");
    lv_obj_set_style_text_color(uiSecSplit, lv_color_hex(0x808080),
                                LV_CU_BASE_STYLE);

    uiSecValue = lv_label_create(uiSecGroup);
    lv_obj_set_size(uiSecValue, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiSecValue, 3, 0);
    lv_obj_set_align(uiSecValue, LV_ALIGN_CENTER);
    lv_label_set_text(uiSecValue, "--");
    lv_obj_set_style_text_color(uiSecValue, lv_color_hex(0x9A9A9A),
                                LV_CU_BASE_STYLE);
  }

  lv_obj_add_event_cb(scr, screenLoadEvent, LV_EVENT_SCREEN_LOADED, this);
}

static void screenLoadEvent(lv_event_t *e) {
  Home *home = (Home *)lv_event_get_user_data(e);

  leftAnimation(home->uiHourGroup, 0);
}

int32_t _ui_anim_callback_get_opacity(lv_anim_t *a) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  return lv_obj_get_style_opa(usr->target, 0);
}

void _ui_anim_callback_set_opacity(lv_anim_t *a, int32_t v) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  lv_obj_set_style_opa(usr->target, v, 0);
}

void _ui_anim_callback_set_x(lv_anim_t *a, int32_t v) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  lv_obj_set_x(usr->target, v);
}
void _ui_anim_callback_free_user_data(lv_anim_t *a) {
  lv_mem_free(a->user_data);
  a->user_data = NULL;
}

int32_t _ui_anim_callback_get_x(lv_anim_t *a) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  return lv_obj_get_x_aligned(usr->target);
}

static void leftAnimation(lv_obj_t *obj, int delay) {
  ui_anim_user_data_t *animation =
      (ui_anim_user_data_t *)lv_mem_alloc(sizeof(ui_anim_user_data_t));
  animation->target = obj;
  animation->val = -1;
  lv_anim_t PropertyAnimation_0;
  lv_anim_init(&PropertyAnimation_0);
  lv_anim_set_time(&PropertyAnimation_0, 500);
  lv_anim_set_user_data(&PropertyAnimation_0, animation);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
  lv_anim_set_values(&PropertyAnimation_0, 100, 0);
  lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_overshoot);
  lv_anim_set_deleted_cb(&PropertyAnimation_0,
                         _ui_anim_callback_free_user_data);
  lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
  lv_anim_start(&PropertyAnimation_0);
}

void Home::main_process() {}
void Home::update_clock() {}
