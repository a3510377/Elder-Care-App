#include "app/display.h"

#include <TFT_eSPI.h>

#include "app/home/home.h"

#define APPS_LEN 1

TFT_eSPI tft = TFT_eSPI();

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area,
                   lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors(&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

void Display::init() {
  lv_init();

  tft.begin();
  tft.setRotation(1);  // Landscape orientation

  /* Initialize the display */
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = TFT_HEIGHT;
  disp_drv.ver_res = TFT_WIDTH;
  disp_drv.flush_cb = my_disp_flush;
  lv_disp_drv_register(&disp_drv);

  // https://docs.lvgl.io/latest/en/html/porting/indev.html
  /* Initialize the (dummy) input device driver */
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);

  indev_drv.type = LV_INDEV_TYPE_ENCODER;
}

void Display::routine() {
  lv_task_handler();

  int new_index = _now_app;

  return run_app();
  // if (_app != NULL) {
  //   if (action != Action::BACK) return run_app();
  //   kill_app();
  // }
  // // else if (action == Action::FORWARD) {
  // //   // kill_app();
  // //   // _now_app++;
  // //   // setup_app();
  // //   // run_app();
  // // } else if (action == Action::TURN_LEFT) new_index--;
  // // else if (action == Action::TURN_RIGHT) new_index++;

  // // if (new_index != _now_app || _app == NULL) {
  // if (new_index > APPS_LEN) _now_app = 0;
  // else if (new_index < 0) _now_app = APPS_LEN - 1;

  // kill_app();
  // setup_app();
  // run_app();
}

void Display::setup_app() {
  Serial.println("setup app");
  switch (_now_app) {
    case 0:
      _app = new Home();
      break;
  }
  Serial.println("setup app done");
}

void Display::run_app() {
  // _app->main_process();
}

void Display::kill_app() {
  if (_app != NULL) delete _app;
}

void Display::setBrightness(int value, int maxValue) {
  // TODO
}
