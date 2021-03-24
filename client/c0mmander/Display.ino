#include <LiquidCrystal_I2C.h>

byte arrow1[] = { 0x0C, 0x11, 0x13, 0x11, 0x11, 0x19, 0x11, 0x06 };
byte arrow2[] = { 0x0E, 0x05, 0x11, 0x11, 0x11, 0x11, 0x15, 0x0E };

class Display {
  private:
    LiquidCrystal_I2C *_lcd;
  
  public:
    Display(LiquidCrystal_I2C *lcd) {
      _lcd = lcd;
    }

    void init() {
      _lcd->init();
      _lcd->backlight();
    }

    void printStatus(String status) {
      _lcd->clear();
      _lcd->setCursor(0, 0);
      _lcd->print(status);
    }

    
    void printC0mmand(String c0mmandName) {
      _lcd->setCursor(0, 0);
      _lcd->print("+------------------+");
      _lcd->setCursor(0, 1);
      _lcd->print(c0mmandName);
      _lcd->setCursor(0, 2);
      _lcd->print("+------------------+");
    }
};
