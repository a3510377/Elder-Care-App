#include "utils/info.h"

#include <esp_adc_cal.h>

#include "variable.h"

uint32_t readADC(int ADC_Raw) {
  esp_adc_cal_characteristics_t adc_chars;

  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100,
                           &adc_chars);

  return esp_adc_cal_raw_to_voltage(ADC_Raw, &adc_chars);
}

float parseTemperature(StateInfo *info) {
  return readADC(analogRead(LM35_PIN)) / 91;
}

int parseHeart(StateInfo *info) {
  return range(60, int(info->pulse.getBeatsPerMinute()), 110);
}
