#include <Arduino.h>

#include "app/ui.h"

void animCallbackSetX(void *obj, int32_t v) {
  lv_obj_set_x((lv_obj_t *)obj, v);
}

int32_t animCallbackGetX(lv_anim_t *a) {
  return lv_obj_get_x_aligned((lv_obj_t *)(a->var));
}

void animCallbackSetY(void *obj, int32_t v) {
  lv_obj_set_y((lv_obj_t *)obj, v);
}

int32_t animCallbackGetY(lv_anim_t *a) {
  return lv_obj_get_y_aligned((lv_obj_t *)(a->var));
}
