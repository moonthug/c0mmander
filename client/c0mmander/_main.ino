#include <LiquidCrystal_I2C.h>

#define ROTARY_PIN 33
#define BUTTON_PIN 26

int buttonState = 0;
int rotaryState = 0;


RotarySwitch rotarySwitch = RotarySwitch(ROTARY_PIN);
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Serial.begin(115200);  
  pinMode(BUTTON_PIN, INPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);

  if (rotarySwitch.isNewValue()) {
      Serial.println("CHANGE!");
      Serial.println(rotarySwitch.getValue());

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(rotarySwitch.getValue());
  }
  
  lcd.setCursor(0, 2);
  lcd.print(buttonState);
}
