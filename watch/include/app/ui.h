#pragma once

#include <lvgl.h>

#define ICON_WIFI ""        // 0xe63e
#define ICON_WIFI_FIND ""   // 0xeb31
#define ICON_HEART ""       // 0xe87d
#define ICON_BOLT ""        // 0xea0b
#define ICON_FOOTPRINT ""   // 0xe566
#define ICON_THERMOSTAT ""  // 0xe1ff

/** Describes an animation*/
typedef struct _ui_anim_user_data_t {
  lv_obj_t *target;
  lv_img_dsc_t **imgset;
  int32_t imgset_size;
  int32_t val;
} ui_anim_user_data_t;

void animCallbackSetX(void *, int32_t);
int32_t animCallbackGetX(lv_anim_t *);
void animCallbackSetY(void *, int32_t);
int32_t animCallbackGetY(lv_anim_t *);

#ifdef __cplusplus
extern "C" {
#endif

LV_FONT_DECLARE(fontIcon);
LV_FONT_DECLARE(fontNumberBig);
LV_FONT_DECLARE(fontNumberExtra);
LV_FONT_DECLARE(fontChinese);

#ifdef __cplusplus
} /*extern "C"*/
#endif
