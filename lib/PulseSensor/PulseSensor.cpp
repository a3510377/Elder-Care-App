#include "PulseSensor.h"

/*
refer to & Part of the program source:
- https://pulsesensor.com/pages/pulse-sensor-amped-arduino-v1dot1
- https://github.com/WorldFamousElectronics/PulseSensorPlayground
*/

// Initialize PulseSensor
void PulseSensor::begin() {
  pinMode(_switch_pin, OUTPUT);

  _sampleIntervalMs = 2000UL / 1000;
  _thresholdSetting = _threshold;
  _resetVariables();
}

void PulseSensor::_resetVariables() {
  for (int i = 0; i < 10; ++i) {
    _rate[i] = 0;
  }
  _QS = false;
  _BPM = 0;
  _IBI = 750;  // 750ms per beat = 80 Beats Per Minute (BPM)
  _pulse = false;
  _sampleCounter = 0;
  _lastBeatTime = 0;
  _p = 512;  // peak at 1/2 the input range of 0..1023
  _t = 512;  // trough at 1/2 the input range.
  // reset the thresh variable with user defined THRESHOLD
  _threshold = _thresholdSetting;
  _amp = 100;           // beat amplitude 1/10 of input range.
  _firstBeat = true;    // looking for the first beat
  _secondBeat = false;  // not yet looking for the second beat in a row
}

// Turn off PulseSensor
void PulseSensor::stop() {
  digitalWrite(_switch_pin, LOW);
  _state = false;
}

// Turn on PulseSensor
void PulseSensor::start() {
  digitalWrite(_switch_pin, HIGH);
  _state = true;
}

void PulseSensor::read() {
  uint16_t signal = analogRead(_pin);
  Serial.print("signal:");
  Serial.println(signal);

  // keep track of the time in mS with this variable
  _sampleCounter += _sampleIntervalMs;
  // monitor the time since the last beat to avoid noise
  _n = _sampleCounter - _lastBeatTime;

  // find the peak and trough of the pulse wave
  // avoid dichrotic noise by waiting 3/5 of last IBI
  if (signal < _threshold && _n > (_IBI / 5) * 3) {
    if (signal < _t) {  // T is the trough
      _t = signal;      // keep track of lowest point in pulse wave
    }
  }

  // thresh condition helps avoid noise
  if (signal > _threshold && signal > _p) {
    _p = signal;  // P is the peak
  }               // keep track of highest point in pulse wave

  //  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
  // signal surges up in value every time there is a pulse
  if (_n > 250) {  // avoid high frequency noise
    if ((signal > _threshold) && (_pulse == false) && (_n > (_IBI / 5) * 3)) {
      _pulse = true;  // set the Pulse flag when we think there is a pulse
      // measure time between beats in mS
      _IBI = _sampleCounter - _lastBeatTime;
      _lastBeatTime = _sampleCounter;  // keep track of time for next pulse

      if (_secondBeat) {  // if this is the second beat, if secondBeat == TRUE
        _secondBeat = false;            // clear secondBeat flag
        for (int i = 0; i <= 9; i++) {  // seed the running total to get a
                                        // realisitic BPM at startup
          _rate[i] = _IBI;
        }
      }

      if (_firstBeat) {  // if it's the first time we found a beat, if firstBeat
                         // == TRUE
        _firstBeat = false;  // clear firstBeat flag
        _secondBeat = true;  // set the second beat flag
        // IBI value is unreliable so discard it
        return;
      }

      // keep a running total of the last 10 IBI values
      word runningTotal = 0;  // clear the runningTotal variable

      for (int i = 0; i <= 8; i++) {  // shift data in the rate array
        _rate[i] = _rate[i + 1];      // and drop the oldest IBI value
        runningTotal += _rate[i];     // add up the 9 oldest IBI values
      }

      _rate[9] = _IBI;           // add the latest IBI to the rate array
      runningTotal += _rate[9];  // add the latest IBI to runningTotal
      runningTotal /= 10;        // average the last 10 IBI values
      // how many beats can fit into a minute? that's BPM!
      _BPM = 60000 / runningTotal;
      _QS = true;  // set Quantified Self flag (we detected a beat)
    }
  }

  // when the values are going down, the beat is over
  if (signal < _threshold && _pulse == true) {
    _pulse = false;              // reset the Pulse flag so we can do it again
    _amp = _p - _t;              // get amplitude of the pulse wave
    _threshold = _amp / 2 + _t;  // set thresh at 50% of the amplitude
    _p = _threshold;             // reset these for next time
    _t = _threshold;
  }

  if (_n > 2500) {                   // if 2.5 seconds go by without a beat
    _threshold = _thresholdSetting;  // set thresh default
    _p = 512;                        // set P default
    _t = 512;                        // set T default
    _lastBeatTime = _sampleCounter;  // bring the lastBeatTime up to date
    _firstBeat = true;               // set these to avoid noise
    _secondBeat = false;             // when we get the heartbeat back
    _QS = false;
    _BPM = 0;
    _IBI = 600;  // 600ms per beat = 100 Beats Per Minute (BPM)
    _pulse = false;
    _amp = 100;  // beat amplitude 1/10 of input range.
  }
}
