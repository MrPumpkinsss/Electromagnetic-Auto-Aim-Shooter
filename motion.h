#ifndef __MOTION_H
#define __MOTION_H

#include <Arduino.h>
#include "aim.h"
#include "blue.h"
#include "iic.h"

void scan();
void safety();
void fire();
void hold();
void reload();
int pinVotage(int pin);
void votageStatu();
void motionInit();
void disarm();
void beep(int times, int duration);
#endif
