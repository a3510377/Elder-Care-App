#pragma once

#include <Adafruit_ADXL345_U.h>
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <PulseSensor.h>
#include <SPIFFS.h>
#include <WebSocketsClient.h>
#include <Wire.h>

#include "app/display.h"
#include "network.h"

struct Context {
  WebSocketsClient *ws;
  PulseSensor *pulse;
  Adafruit_BMP085 *bmp;
  Adafruit_ADXL345_Unified *accel;

  Display *screen;
  Network *network;
};

static void TaskTFT(void *);
