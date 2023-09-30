#pragma once
#include <Arduino.h>

#ifndef DEFAULT_PULSE_THRESHOLD
  #define DEFAULT_PULSE_THRESHOLD 475
#endif

class PulseSensor {
 public:
  PulseSensor(uint8_t pin) : _pin(pin), _threshold(DEFAULT_PULSE_THRESHOLD) {}
  PulseSensor(uint8_t pin, uint8_t switch_pin)
      : _pin(pin),
        _switch_pin(switch_pin),
        _threshold(DEFAULT_PULSE_THRESHOLD) {}
  PulseSensor(uint8_t pin, uint8_t switch_pin, uint16_t threshold)
      : _pin(pin), _switch_pin(switch_pin), _threshold(threshold) {}

  void begin(void);

  void stop(void);
  void start(void);
  void read(void);

  inline int getBeatsPerMinute(void) {
    return _BPM;
  }

 protected:
  uint8_t _pin, _switch_pin;
  volatile int _thresholdSetting;

  int _t, _n, _p, _threshold;
  bool _secondBeat, _firstBeat;
  volatile bool _pulse, _QS;
  volatile int _BPM, _IBI, _amp;

  volatile u_long _lastBeatTime, _sampleIntervalMs, _sampleCounter;
  int _rate[10];  // array to hold last ten IBI values (ms)
  void _resetVariables(void);
};
