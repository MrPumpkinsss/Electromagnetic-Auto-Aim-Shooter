#ifndef __BLUE_H
#define __BLUE_H

#include "SoftwareSerial.h"
#include <Arduino.h>
#include "aim.h"

void blueInit();
int blueReceive();
void blueSend(String text);

#endif
