#ifndef __AIM_CPP
#define __AIM_CPP

#include "aim.h"

//Servo servo_x;
//Servo servo_y;  

int ctr_x = 330; //320
int ctr_y = 227; //240
int servo_x_pos = 1500;
int servo_y_pos = 1500;
int offsetx = 0;
int offsety = 0;
int Servo_clr = 1;
double Setpointx, Inputx, Outputx;
double Setpointy, Inputy, Outputy;
double Kp=0.25, Ki=0.04, Kd=0.01;
PID PIDx(&Inputx, &Outputx, &Setpointx, Kp, Ki, Kd, DIRECT);
PID PIDy(&Inputy, &Outputy, &Setpointy, Kp, Ki, Kd, DIRECT);

void servoInit(){
  //servo_x.attach(6);
  //servo_y.attach(5);    
  //servo_x.write(90);
  //servo_y.write(90);
  pinMode(servo_x, OUTPUT);
  pinMode(servo_y, OUTPUT);
  servoPulse(servo_x,1500);
  servoPulse(servo_y,1500);
  PIDx.SetOutputLimits(-200, 200);
  PIDy.SetOutputLimits(-200, 200);
  PIDx.SetMode(AUTOMATIC);
  PIDy.SetMode(AUTOMATIC);
  //Serial.println("Servo ready");
}

void aimInit(){
  int offsetx = 0;
  int offsety = 0;
  double Outputx = 0;
  double Outputy = 0;  
  servo_x_pos = 1500;
  servo_y_pos = 1500;
  servoInit();
  //PIDx.Compute();
  //PIDy.Compute();
  delay(10);
}

void aim(){
  if(axisx()>0&axisy()>0){
    Inputx = axisx();
    Inputy = axisy();
    Setpointx = ctr_x;
    Setpointy = ctr_y;
    PIDx.Compute();
    PIDy.Compute();
    Serial.print(axisx());
    Serial.print(" ");
    Serial.println(axisy());
    Outputy = Outputy/1.5;
    if(abs(Inputx-ctr_x)<4){
      Outputx =0;  
    }
    if(abs(Inputy-ctr_y)<4){
      Outputy =0;  
    }
    if(abs(Inputy-ctr_y)<8 & abs(Inputx-ctr_x)<8){
      blueSend("Ready");
    }
    else{
      blueSend("Not Ready");
    }
    servo_x_pos = servo_x_pos + round(Outputx);
    servo_y_pos = servo_y_pos - round(Outputy);
    servo_x_pos = constrain(servo_x_pos,550,2450);
    servo_y_pos = constrain(servo_y_pos,550,2450);
    servoPulse(servo_x,servo_x_pos);
    servoPulse(servo_y,servo_y_pos);
    Serial.print(servo_x_pos);
    Serial.print(" ");
    Serial.println(servo_y_pos);
    delay(30);
  }
  delay(20);
}

void servoPulse(int servoPin, int angle)//定义一个脉冲函数
{
  Servo_clr = 0;
  //发送1个脉冲
  if(servoPin == 6){
    angle -= 50;
    angle = constrain(angle,1000,2000);
  }
  else{
    angle = constrain(angle,1000,1800);
  }
  delay(5);
  for (int i = 0; i < 1; i++) {
    int pulsewidth = angle;
    digitalWrite(servoPin, HIGH);   //将舵机接口电平至高
    delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数
    digitalWrite(servoPin, LOW);    //将舵机接口电平至低
    delayMicroseconds(20000 - pulsewidth);
  }
  delay(10);
  Servo_clr = 1;
}

void servoDegree(int servoPin, int angle)//定义一个脉冲函数
{
  //发送50个脉冲
  for (int i = 0; i < 2; i++) {
    int pulsewidth = angle * 11 + 500;
    digitalWrite(servoPin, HIGH);   //将舵机接口电平至高
    delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数
    digitalWrite(servoPin, LOW);    //将舵机接口电平至低
    delayMicroseconds(20000 - pulsewidth);
  }
}

int Servo_stat(){
  return Servo_clr;
}

#endif
