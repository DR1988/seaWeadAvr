/*
 * zStepper.h
 *
 * Created: 10/11/2022 2:08:43 AM
 *  Author: DR
 */ 


#ifndef ZSTEPPER_H_
#define ZSTEPPER_H_

struct Stepper{
	volatile unsigned int steps_to_do;
	volatile unsigned int done_steps;
};

void enableZ();
void disableZ();
void forwardZ();
void backwardZ();
void stepZ();
void runZStepper();

void setupZaxis();
int isZAxisStepperEnable();

int decodeZCommand(volatile unsigned char commands[], int mainLoop);


#endif /* ZSTEPPER_H_ */