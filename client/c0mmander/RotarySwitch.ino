#define CHANNEL_COUNT COMMAND_COUNT
#define READING_COUNT 5

class RotarySwitch {
  private:
    int _channels[CHANNEL_COUNT][2] = { 
      { 0, 2999 },    // 0
      { 2999, 3149 }, // 1
      { 3149, 3259 }, // 2
      { 3259, 3499 }, // 3
      { 3499, 3650 }, // 4
      { 3650, 3710 }, // 5
      { 3710, 3799 }, // 6
      { 3799, 3890 }, // 7
      { 3890, 3980 }, // 8
      { 3980, 4020 }, // 9
      { 4020, 4075 }, // 10
      { 4075, 5000 }  // 11
    };
    
    int _pin;
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
      
      int currAnalogVal = analogRead(_pin);

      _readings[READING_COUNT - 1] = currAnalogVal;
      total += currAnalogVal;

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
