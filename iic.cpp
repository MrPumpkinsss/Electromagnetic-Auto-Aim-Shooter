#ifndef __IIC_CPP
#define __IIC_CPP

#include "iic.h"
const char* dataR;
int numx = 0;
int numy = 0;
int i =0;

void receiveData(int byteCount) {  //事件触发iic从机函数
  if(Servo_stat() == 1){
    delay(10);
    numx = 0; numy = 0;
    String receivedData;
    while(Wire.available()) {
      char c = Wire.read();
      receivedData += c;
    }
    dataR = receivedData.c_str();
    if(strlen(dataR)==7){
      //Serial.println(receivedData);
      for(i=1; i<4; i++){
        //Serial.println(receivedData[i]);
        numx = numx*10 + (receivedData[i]-48);  //将字符串转为整形
      }
      for(i=4; i<7; i++){
        numy = numy*10 + (receivedData[i]-48);
      }
      numx = constrain(numx,0,640);
      numy = constrain(numy,0,480);
      delay(40);
    }
    else{
      delay(40);
    }
  }
}

void iicInit(){  //iic初始化函数
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Serial.println("IIC ready");
  delay(100);
}


int axisx(){  //返回数据
  return numx;
  delay(5);
}

int axisy(){
  return numy;
  delay(5);
}

#endif
