#define CHANNEL_COUNT 12
#define READING_COUNT 15

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
        this->_readings[i] = this->_readings[i+1];

        // Add to total;
        total += this->_readings[i];
      }
      
      int currAnalogVal = analogRead(this->_pin);

      this->_readings[READING_COUNT - 1] = currAnalogVal;
      total += currAnalogVal;

      return floor(total / READING_COUNT);
    }
  
  public:
    RotarySwitch(int pin) {
      this->_pin = pin;
      this->_value = 0;

      for (int i = 0; i < READING_COUNT; i++) {
        this->_readings[i] = 0;
      }
    }

    bool isNewValue() {
      int currentValue = this->_value;
      int currAvgVal = this->_getReading();
      int diff = currAvgVal - this->_lastAvgVal;

      if (abs(diff) > 10) {
        for(int i = 0; i < CHANNEL_COUNT; i++) {
          if (currAvgVal >= this->_channels[i][0] && currAvgVal < this->_channels[i][1]) {
            this->_value = i;
            break;
          }
        }
      }
      
      this->_lastAvgVal = currAvgVal;
      
      return this->_value != currentValue;
    }

    int getValue() {
      return this->_value;
    }
};
