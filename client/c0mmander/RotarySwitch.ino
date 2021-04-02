#define CHANNEL_COUNT COMMAND_COUNT
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

    int _getReading() {
      int total = 0;

      for(int i = 0; i < READING_COUNT - 1; i++) {
        // Shift array
        _readings[i] = _readings[i+1];

        // Add to total;
        total += _readings[i];
      }
      
      _currAnalogVal = analogRead(_pin);

//      Serial.println(_currAnalogVal);

      _readings[READING_COUNT - 1] = _currAnalogVal;
      total += _currAnalogVal;

      return floor(total / READING_COUNT);
    }
  
  public:
    RotarySwitch(int pin) {
      _pin = pin;
      _value = 0;

      for (int i = 0; i < READING_COUNT; i++) {
        _readings[i] = 0;
      }
    }

    bool isNewValue() {
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

    int getValue() {
      return _value;
    }
};
