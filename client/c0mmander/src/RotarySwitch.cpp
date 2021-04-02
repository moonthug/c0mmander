#include "RotarySwitch.h"

int RotarySwitch::_getReading() {
  int total = 0;

  for(int i = 0; i < READING_COUNT - 1; i++) {
    // Shift array
    _readings[i] = _readings[i+1];

    // Add to total;
    total += _readings[i];
  }
  
  _currAnalogVal = analogRead(_pin);

  //Serial.println(_currAnalogVal);

  _readings[READING_COUNT - 1] = _currAnalogVal;
  total += _currAnalogVal;

  return floor(total / READING_COUNT);
}

RotarySwitch::RotarySwitch(int pin) {
  _pin = pin;
  _value = 0;

  for (int i = 0; i < READING_COUNT; i++) {
    _readings[i] = 0;
  }
}

bool RotarySwitch::isNewValue() {
  int currentValue = _value;
  int currAvgVal = _getReading();
  int diff = currAvgVal - _lastAvgVal;

  if (abs(diff) > 10) {
    for(int i = 0; i < CHANNEL_COUNT; i++) {
      if (currAvgVal >= _channels[i][0] && currAvgVal < _channels[i][1]) {
        _value = i;
        break;
      }
    }
  }
  
  _lastAvgVal = currAvgVal;
  
  return _value != currentValue;
}

int RotarySwitch::getValue() {
  return _value;
}