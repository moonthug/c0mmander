#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class Display {
  private:
    LiquidCrystal_I2C *_lcd;
  
  public:
    Display(LiquidCrystal_I2C *lcd);

    void init();
    void printStatus(String status);
    void printC0mmand(String c0mmandName);
};

#endif