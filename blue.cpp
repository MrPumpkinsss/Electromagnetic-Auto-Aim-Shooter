#ifndef __BLUE_CPP
#define __BLUE_CPP

#include "blue.h"

char receivedChar;
SoftwareSerial blue(10, 11); // TX, RX

void blueInit(){
  blue.begin(9600); 
  Serial.println("Bluetooth ready");
}

int blueReceive(){
  if(Servo_stat() == 1){
    if (blue.available() > 0) {
      receivedChar = blue.read();
      blue.print(receivedChar);
    }
    delay(20);
    return receivedChar;
  }
}

void blueSend(String text){
  if(Servo_stat() == 1){
    char buf[text.length()];
    memcpy(buf, text.c_str(), text.length());
    blue.write(buf, text.length());
    delay(20);
  }
}
#endif
