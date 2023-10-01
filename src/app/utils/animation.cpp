#include <Arduino.h>

#include "app/ui.h"

void animCallbackSetOpacity(void *var, int32_t v) {
  Serial.println(v);
  lv_obj_set_style_opa((_lv_obj_t *)var, v, 0);
}
