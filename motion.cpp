#ifndef __MOTION_CPP
#define __MOTION_CPP

#include "motion.h"

int safe = 1;

void scan(){
  servoPulse(servo_y,1500);
  blueSend("---Starting Scan---");
  while(1){
    for(int i=1500;i<1800;i+=10){
      if((axisx()!=0)|(blueReceive()==48)){
        break;  
      }
      servoPulse(servo_x,i);
      Serial.println(axisx());
      delay(2);
    }
    for(int i=1800;i>1200;i-=10){
      if((axisx()!=0)|(blueReceive()==48)){
        break;  
      }
      servoPulse(servo_x,i);
      Serial.println(axisx());
      delay(2);
    }
    for(int i=1200;i<1500;i+=10){
      if((axisx()!=0)|(blueReceive()==48)){
        break;  
      }
      servoPulse(servo_x,i);
      Serial.println(axisx());
      delay(2);
    }
    if((axisx()!=0)|(blueReceive()==48)){
      break;
    }
  }
  if(axisx()!=0){
    blueSend("----Target Found----");
  }
}

void safety(){
  safe = 0;
  blueSend("------Safety is off, ready to fire------");
}

void disarm(){
  blueSend("--Disarming--");
  beep(2,100);
  servoPulse(servo_x,1500);
  servoPulse(servo_y,1500);
  for(int i=1500;i<2000;i+=5){
    servoPulse(servo_y,i);
    delay(2);
  }
  delay(1000);
  for(int i=2000;i>1500;i-=5){
    servoPulse(servo_y,i);
    delay(2);
  }
  
}

void fire(){
  //if(safe == 0){
    delay(10);
    blueSend("------Caution, firing------");
    //safe = 1;
    beep(3,100);
    votageStatu();
    delay(1000);
    digitalWrite(3,HIGH);
    delay(10000);
    //delay(2000);
    digitalWrite(3,LOW);
    votageStatu();
    beep(3,50);
    digitalWrite(2,HIGH);
    delay(100);
    digitalWrite(2,LOW);
    delay(700);
    digitalWrite(4,HIGH);
    delay(100);
    digitalWrite(4,LOW);
    votageStatu();
    //safe = 1;
  //}
  //else{
    //blueSend("Fail, safety is activated!");
  //}
}

void hold(){
  servoPulse(servo_x,1500);
  servoPulse(servo_y,1500);
  delay(10);
}

void reload(){
  blueSend("--Setting to reload position--");
  beep(2,100);
  servoPulse(servo_x,1500);
  servoPulse(servo_y,1500);
  for(int i=1500;i>1000;i-=5){
    servoPulse(servo_y,i);
    delay(2);
  }
  delay(4000);
  beep(3,100);
  for(int i=1000;i<1500;i+=5){
    servoPulse(servo_y,i);
    delay(7);
  }
  safe = 0;
}

int pinVotage(int pin){
  int voltage = analogRead(pin); //读取io口模拟值
  return voltage; //返回值
}

void votageStatu(){
  String A1statu = "Safe";
  String A2statu = "Safe";
  if (pinVotage(A1)>5){
    A1statu = "Charged";
  }
  if (pinVotage(A2)>15){
    A2statu = "Charged";
  }
  Serial.println("A1 "+A1statu+" "+pinVotage(A1)+"  A2 "+A2statu+" "+pinVotage(A2));
  blueSend("A1 "+A1statu+" "+pinVotage(A1)+"  A2 "+A2statu+" "+pinVotage(A2));
}

void motionInit(){
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);  
}

void beep(int times, int duration){
  for(int i=0;i<times;i++){
    digitalWrite(4,HIGH);  
    delay(duration);
    digitalWrite(4,LOW);
    delay(duration);
  }
}

#endif
