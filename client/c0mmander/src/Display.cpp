#include "Display.h"

Display::Display(LiquidCrystal_I2C *lcd) {
  _lcd = lcd;
}

void Display::init() {
  _lcd->init();
  _lcd->backlight();     
//    _lcd->createChar(0, arrow1);
//    _lcd->createChar(1, arrow2);
}

void Display::printStatus(String status) {
  _lcd->clear();
  _lcd->setCursor(0, 0);
  _lcd->print(status);
}

void Display::printC0mmand(String c0mmandName) {
  _lcd->setCursor(0, 0);
  _lcd->print("+------------------+");
  _lcd->setCursor(0, 1);
  _lcd->print(c0mmandName);
  _lcd->setCursor(0, 2);
  _lcd->print("+------------------+");
}
