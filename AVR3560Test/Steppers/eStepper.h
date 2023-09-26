/*
 * eStepper.h
 *
 * Created: 8/21/2023 11:35:14 PM
 *  Author: DR
 */ 


#ifndef ESTEPPER_H_
#define ESTEPPER_H_

struct Stepper{
	volatile unsigned int steps_to_do;
	volatile unsigned int done_steps;
};

void enableE();
void disableE();
void forwardE();
void backwardE();
void stepE();
void runEStepper();

void setupEaxis();
int isEAxisStepperEnable();

int decodeECommand(volatile unsigned char commands[], int mainLoop);



#endif /* ESTEPPER_H_ */