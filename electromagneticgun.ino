#include "iic.h"
#include "aim.h"
#include "blue.h"
#include "motion.h"
#include "song.h"
//sudo i2cdetect -y 1
//A4（SDA）white    A5（SCL）black
//servox D6    servoy D5
//TXD D10    RXD D11
//Charge pin 3  Fire pin 2

//  servox pin 7
//  servoy pin 8

int choice = 0;
int fireOK=0; int reloadOK=0; int defaultOK=0; int aimOK=0; int disarmOK=0;


void setup() {
  Serial.begin(9600);
  iicInit(); //初始化iic从机接收
  servoInit();
  blueInit();
  pinMode(13,OUTPUT);
  motionInit();
  blueSend("\n \n \n");
  //blueSend("\n0 Stop&Reset counter\n1 Scan\n2 Safety\n3 Fire\n4 Reload");
  votageStatu();
  //beep(2,100);
  //nokia();
}

void loop() {
  choice = blueReceive()-48;
  switch(choice){
    case 0:
      hold();
      aimInit();
      fireOK = 1;
      reloadOK = 1;
      defaultOK = 1;
      aimOK = 1;
      disarmOK = 1;
      delay(1000);
      break;
    case 2:
      if(aimOK == 1){
        scan();
        while(blueReceive()==50){
          aim();  
        }
      }
      aimOK = 0;
      break;
    case 4:
      if(fireOK == 1){
        fire();
      }
      fireOK = 0;
      break;
    case 1:
      if(reloadOK == 1){
        reload();
      }
      reloadOK = 0;
      break;
    case 5:
      votageStatu();
      delay(3000);
      break;
    case 6:
      if(disarmOK == 1){
        disarm();
      }
      disarmOK = 0;
      break;
    default:
      if(defaultOK == 1){
        hold();
        votageStatu();
      }
      defaultOK = 0;
      break;
  }
  delay(50);
}
