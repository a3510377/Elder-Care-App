#pragma once

#include <lvgl.h>

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

LV_IMG_DECLARE(imageBattery);
LV_FONT_DECLARE(fontNumberBig);
LV_FONT_DECLARE(fontNumberExtra);

#ifdef __cplusplus
} /*extern "C"*/
#endif
