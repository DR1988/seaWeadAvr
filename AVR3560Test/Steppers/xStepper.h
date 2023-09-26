/*
 * xStepper.h
 *
 * Created: 10/10/2022 2:33:21 AM
 *  Author: DR
 */ 
#ifndef XSTEPPER_H_
#define XSTEPPER_H_

struct Stepper{
	 volatile unsigned int steps_to_do;
	 volatile unsigned int done_steps;
};

void enableX();
void disableX();
void forwardX();
void backwardX();
void stepX();
void runXStepper();

void setupXaxis();
int isXAxisStepperEnable();

int decodeXCommand(volatile unsigned char commands[], int mainLoop);

#endif /* XSTEPPER_H_ */