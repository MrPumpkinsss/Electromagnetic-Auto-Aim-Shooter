#ifndef __AIM_H
#define __AIM_H

#include <Arduino.h>
#include "iic.h"
#include <PID_v1.h>
#include <Servo.h>
#include "blue.h"
  
#define servo_x 6
#define servo_y 5

void servoInit();
void aim();
void PIDcalculation();
void servoPulse(int servoPin, int angle);
void servoDegree(int servoPin, int angle);
void aimInit();
int Servo_stat();

#endif
