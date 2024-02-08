/*
 * yStepper.h
 *
 * Created: 10/11/2022 1:10:53 AM
 *  Author: DR
 */ 


#ifndef YSTEPPER_H_
#define YSTEPPER_H_

struct Stepper{
	volatile unsigned long steps_to_do;
	volatile unsigned long done_steps;
};

void enableY();
void disableY();
void forwardY();
void backwardY();
void stepY();
void runYStepper();

void setupYaxis();
int isYAxisStepperEnable();

int decodeYCommand(volatile unsigned char commands[], int mainLoop);



#endif /* YSTEPPER_H_ */