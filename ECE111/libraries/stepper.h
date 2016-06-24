#ifndef INCLUDED_STEPPER_H
#define INCLUDED_STEPPER_H

#include "delay.h"

void runStepperMotor( unsigned short int direction,  int time, int stepNumber );
void takeStep(void);

#endif
