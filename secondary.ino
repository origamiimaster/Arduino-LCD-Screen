#include <LiquidCrystal_I2C.h>
String inputString = "";
bool stringComplete = false;
int incomingByte = 0;
bool sentReady = false;
bool gotReady = false;
LiquidCrystal_I2C lcd(0x3F, 20,4);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("Waiting to establish connection");
  Serial.begin(9600); 
  pinMode(12, OUTPUT);
}

void loop() {
  if(gotReady){
    digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);    
  } else if(!sentReady){
    digitalWrite(12, LOW);
    Serial.print("START\n");
    sentReady = true;
  } else {
    if(stringComplete){
      Serial.print(inputString);
      if(inputString == "READY\n"){
        lcd.clear();
        lcd.print("Connection Established Press Switch to run test");
        digitalWrite(12, HIGH);
        gotReady = true;
      }
      inputString = "";
      stringComplete = false;
    }
  }
}

void serialEvent(){
  while(Serial.available()){
    char inChar = (char)Serial.read();
    inputString += inChar;
    if(inChar == '\n'){
      stringComplete = true;
//      Serial.print(inputString);
    }
    
  }
  
}
