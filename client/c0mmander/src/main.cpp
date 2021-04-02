#include <Arduino.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

#include "Display.h"
#include "C0mmandService.h"
#include "RotarySwitch.h"
#include "config.h"

#define ROTARY_PIN 33
#define BUTTON_PIN 26

int frame = 0;
int c0mmandId = 0;
int c0mmandCount = 0;

bool loading = false;

LiquidCrystal_I2C lcd(0x27, 20, 4);

Display display = Display(&lcd);
C0mmandService c0mmandService = C0mmandService(c0mmandBaseUrl);
RotarySwitch rotarySwitch = RotarySwitch(ROTARY_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial) {};

  display.init();
  
  pinMode(BUTTON_PIN, INPUT);

  WiFi.begin(ssid, password);
  WiFi.setHostname("c0mmander");

  display.printStatus("Connecting to wifi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  delay(500);

  loading = true;
  while(c0mmandCount == 0) {
    display.printStatus("Fetch c0mmands...");
    delay(500);
    c0mmandCount = c0mmandService.fetchC0mmands();

    if (c0mmandCount == 0) {
      display.printStatus("Failed to fetch! Retrying...");
      delay(5000);
    }
  }
  
  Serial.print("C0mmands Received: ");
  Serial.println(c0mmandCount);
  
  display.printStatus("c0mmands OK!");
  delay(500);
}

void loop() {
  // Handle rotary switch value change
  if (rotarySwitch.isNewValue()) {      
    lcd.clear();
    c0mmandService.setC0mmandId(rotarySwitch.getValue());
  }

  // Handle button press    
  if (digitalRead(BUTTON_PIN) == HIGH) {
    if (c0mmandService.getState() != EXECUTING_C0MMAND) {
      display.printStatus("Executing c0mmand");
      c0mmandService.executeC0mmand();
      delay(500);
    }
  }

  display.printC0mmand(c0mmandService.getC0mmandName());
  
  frame++;
}