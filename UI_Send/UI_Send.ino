#include "Arduino.h"
#include "heltec.h"

#define RXD2 19
#define TXD2 22

const int buttonPin = 0;
const int ledPin = 25;
const int shortPressTime = 500; // 500 milliseconds
String received = "FRESH";

int lastState = HIGH;
int currentState;
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;
bool boy = true;
bool sent = false;

int buttonState = 0;

void drawUI(){
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0, 0, "It's a Baby");
  Heltec.display->drawString(0, 16, "    Boy");
  Heltec.display->drawString(0, 32, "    Girl");
  if(boy == true){
    Heltec.display->drawString(0, 16, " >");
  } else {
    Heltec.display->drawString(0, 32, " >");
  }
  Heltec.display->display();
}
void setup() {
  // put your setup code here, to run once:
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Heltec.display->flipScreenVertically();

  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  drawUI();
  // read the state of the switch/button:
  currentState = digitalRead(buttonPin);
//  Serial.println(currentState);

  if(lastState == HIGH && currentState == LOW) {       // button is pressed
    pressedTime = millis();
  }
  else if(lastState == LOW && currentState == HIGH) { // button is released
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if( pressDuration < shortPressTime ) {
      Serial.println("A short press is detected");
      sent = false;
      
      if(boy == true){
        boy = false;
      } else {
        boy = true;
      }
      //Add in code to move to lower ui item
    } else {
      Serial.println("A long press is detected");
      digitalWrite(ledPin, HIGH);
      sent = true;
      //Add in code to send item based on ui item
      
    }
  }

  if(sent == true){
    //Send the ping
    digitalWrite(ledPin, HIGH);
    if(boy == true) {
        Serial.println("It's a boy");
        Serial2.print("AT+SEND=0,4,Boy \r\n");
      } else {
        Serial.println("It's a girl");
        Serial2.print("AT+SEND=0,4,Girl\r\n");
      }
  } else {
    digitalWrite(ledPin, LOW);
  }
  // save the the last state
  lastState = currentState;

  if(Serial.available()){
    Serial2.print(Serial.readString()+"\r\n");  
  }
  if(Serial2.available()){
    received = Serial2.readString();
    Serial.print(received);  
    if(received.startsWith("+RCV")){
      Serial.print(received);
    }
  }
}



//void loop() {
//  // put your main code here, to run repeatedly:
//  buttonState = digitalRead(buttonPin);
//
//  if (buttonState == HIGH) {
//    digitalWrite(ledPin, LOW);
//  } else {
//    digitalWrite(ledPin, HIGH);
//  }
//
//}
