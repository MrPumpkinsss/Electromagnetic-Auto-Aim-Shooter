#ifndef __IIC_H
#define __IIC_H

#define SLAVE_ADDRESS 0x08

#include <String.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "aim.h"

void receiveData(int byteCount);
void iicInit();
int axisx();
int axisy();

#endif
