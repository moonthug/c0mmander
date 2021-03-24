#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "";
const char* password = "";
///const char* c0mmandBaseUrl = "http://192.168.1.50:10010";
const char* c0mmandBaseUrl = "http://192.168.1.13:3000";

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

//  lcd.createChar(0, arrow1);
//  lcd.createChar(1, arrow2);
  display.init();
  
  pinMode(BUTTON_PIN, INPUT);

  WiFi.begin(ssid, password);
  
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
  delay(1000);
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
      c0mmandService.executeC0mmand();
      display.printStatus("Executing c0mmand:");
      delay(1000);
    }
  }

  display.printC0mmand(c0mmandService.getC0mmandName());
  
  frame++;
}
