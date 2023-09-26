/*
 * yStepper.c
 *
 * Created: 10/11/2022 1:11:59 AM
 *  Author: DR
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "yStepper.h"

void setupYaxis() {
	DDRF |= (1 << DDF6); //STEPS
	DDRF |= (1 << DDF7);//DIRECTION
	PORTF |= (0 << PF7);//DIRECTION
	DDRF |= (1 << DDF2);//DISABLE
	PORTF |= (1 << PF2);//DISABLE  1 - DISABLE, 0 - ENABLE
}


void enableY() {
	PORTF &= ~(1 << PF2);
}

void disableY() {
	PORTF |= (1 << PF2);
}

void forwardY() {
	PORTF &= ~(1 << PF7);
}

void backwardY() {
	PORTF |= (1 << PF7);
}

void stepY() {
	PORTF ^= (1 << PF6);
	PORTF ^= (1 << PF6);
}

int isYAxisStepperEnable() {
	return ! (PORTF & (1 << PF2));
}

extern struct Stepper yStepper = {0, 0};

void runYStepper() {
	if (yStepper.steps_to_do !=0 && yStepper.done_steps != yStepper.steps_to_do) {
			yStepper.done_steps++;
			stepY();
		} else if (yStepper.steps_to_do != 0 && yStepper.done_steps == yStepper.steps_to_do) {
			yStepper.steps_to_do = 0;
			yStepper.done_steps = 0;
			disableY();
			TransmitString("y_STEPPER_STOP");
		}
}

int decodeYCommand(volatile unsigned char commands[], int mainLoop) {
	unsigned int i = mainLoop;
	unsigned int j = 0;
	unsigned char tempBuf[10];
	while(commands[i] != '|') {
		if (commands[i] == 'E') {
			if (commands[i + 1] == '1') {
				enableY();
				} else {
				disableY();
			}
		}
		
		if (commands[i] == 'D') {
			if (commands[i + 1] == '1') {
				forwardY();
				} else {
				backwardY();
			}
		}
		if (commands[i] == 'S') {
			i += 1;
			while(commands[i] != 'S'){
				tempBuf[j] = commands[i];
				i++;
				j++;
			}
			sscanf(tempBuf, "%d", &yStepper.steps_to_do);
			for (int tempBufCount=0; tempBufCount<10; tempBufCount++){
				tempBuf[tempBufCount] = NULL;
			}
		}
		i++;
	}
	return i;
}
