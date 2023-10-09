#pragma once

#include "app/base.h"

#define range(low, item, hi) max(low, min(item, hi))

uint32_t readADC(int ADC_Raw);
float parseTemperature(StateInfo *info);
int parseHeart(StateInfo *info);
