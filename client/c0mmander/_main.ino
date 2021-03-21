#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

#define ROTARY_PIN 33
#define BUTTON_PIN 26


const char* ssid     = "";
const char* password = "";

const char* c0mmandBaseUrl = "http://192.168.1.23:3000";

int buttonState = 0;
int rotaryState = 0;

String c0mmands;
int c0mmand = 0;

C0mmandService c0mmandService = C0mmandService(c0mmandBaseUrl);
RotarySwitch rotarySwitch = RotarySwitch(ROTARY_PIN);

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Serial.begin(115200);
  
  pinMode(BUTTON_PIN, INPUT);
    
  lcd.init();
  lcd.backlight();

  WiFi.begin(ssid, password);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connnecting to wifi");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  lcd.setCursor(0, 2);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    lcd.print("...");
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connected!");
  
  delay(1000);

  c0mmandService.fetchC0mmands();
}

void loop() {

  lcd.setCursor(0, 0);
  switch(c0mmandService.getState()) {
    case READY:
      lcd.print("FREADY...");
      break;
    case FETCHING_C0MMANDS:
      lcd.print("Fetching c0mmands...");
      break;
    case FETCHING_C0MMANDS_SUCCESS:
      lcd.print("Fetching c0mmands success!");
      break;
    case EXECUTING_C0MMAND:
      lcd.print("Executing c0mmand...");
      break;
    case EXECUTING_C0MMAND_SUCCESS:
      lcd.print("Executing c0mmand success!");
      break;
  }

  buttonState = digitalRead(BUTTON_PIN);

  if (rotarySwitch.isNewValue()) {      
      c0mmand = rotarySwitch.getValue();
      lcd.clear();
      lcd.setCursor(0, 2);
      lcd.print(c0mmand);
  }

  if (buttonState == HIGH) {
    if (c0mmandService.getState() != EXECUTING_C0MMAND) {
      lcd.clear();
      c0mmandService.executeC0mmand(c0mmand);
      delay(50);
    }
  }
}
