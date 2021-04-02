#ifndef ROTARY_SWITCH_H
#define ROTARY_SWITCH_H

#include <Arduino.h>

#define CHANNEL_COUNT 12
#define READING_COUNT 5

class RotarySwitch {
  private:
    int _channels[CHANNEL_COUNT][2] = { 
      { 0, 3200 },    // 0
      { 3200, 3400 }, // 1
      { 3400, 3600 }, // 2
      { 3600, 3700 }, // 3
      { 3700, 3800 }, // 4
      { 3800, 3900 }, // 5
      { 3900, 4000 }, // 6
      { 4000, 4095 }, // 7
      { 4095, 4100 }, // 8
      
      { 4100, 4020 }, // 9 No resitor, the range will never get this high.
      { 4200, 4075 }, // 10
      { 4300, 5000 }  // 11
    };
    int _pin;
    int _currAnalogVal;
    int _readings[READING_COUNT];
    int _lastAvgVal;
    int _value;

    int _getReading();
  
  public:
    RotarySwitch(int pin);

    bool  isNewValue();
    int   getValue();
};

#endif