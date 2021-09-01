#include "Arduino.h"
#include "heltec.h"
#include "lora_config.h"






String received = "FRESH";
void setup() {
  
  
  Serial.begin(115200);
  delay(1000);
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, false /*Serial Enable*/);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  loraSetup();
  Serial.println("Loopback program started");
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(64, 0, "Welcome to");
  Heltec.display->drawString(64, 16, "Jeff and Kelly's");
  Heltec.display->drawString(64, 32, "Gender Reveal!");
  Heltec.display->display();

  //Sponsored by text block
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(64, 53, "Sponsored by Frans :D");
  Heltec.display->display();
   

}

void writeMessage(String message){
  Serial.println("Displaying: "+message);
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_24);
//  Heltec.display->drawString(0, 0, "It's a "+message.substring(9,13));

  // I wrote this entire stupid logic block
  // Just to add an exclamation mark at the end
  if(message.substring(11,15).startsWith("B")){
    Heltec.display->drawString(0, 0, "It's a Boy!");
  } else {
    Heltec.display->drawString(0,0, "It's a Girl!");
  }
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 53, "SSI: "+message.substring(16,19));
  Heltec.display->display();
}

void loop() {

  if(Serial.available()){
    Serial2.print(Serial.readString()+"\r\n");  
  }
  if(Serial2.available()){
    received = Serial2.readString();
    Serial.print(received);  
    if(received.startsWith("+RCV")){
      writeMessage(received);
      Serial.print(received);
    }
  }
}
