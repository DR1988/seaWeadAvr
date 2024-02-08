/*
 * zStepper.c
 *
 * Created: 10/11/2022 2:09:42 AM
 *  Author: DR
 */ 
#include <avr/io.h>
#include <stdio.h>
#include "zStepper.h"

void setupZaxis() {
	DDRK |= (1 << DDK0); //DISABLE
	PORTK |= (1 << PK0);//DISABLE  1 - DISABLE, 0 - ENABLE
	DDRL |= (1 << DDL1); //DIRECTION
	PORTL |= (0 << PL1); //DIRECTION
	DDRL |= (1 << DDL3); //STEPS
}


void enableZ() {
	PORTK &= ~(1 << PK0);
}

void disableZ() {
	PORTK |= (1 << PK0);
}

void forwardZ() {
	PORTL &= ~(1 << PL1);
}

void backwardZ() {
	PORTL |= (1 << PL1);
}

void stepZ() {
	PORTL ^= (1 << PL3);
	PORTL ^= (1 << PL3);
}

int isZAxisStepperEnable() {
	return ! (PORTK & (1 << PK0));
}

extern struct Stepper zStepper = {0, 0};
void runZStepper() {
	if (zStepper.steps_to_do !=0 && zStepper.done_steps != zStepper.steps_to_do) {
		zStepper.done_steps++;
		stepZ();
		} else if (zStepper.steps_to_do != 0 && zStepper.done_steps == zStepper.steps_to_do) {
		zStepper.steps_to_do = 0;
		zStepper.done_steps = 0;
		disableZ();
		TransmitString("z_STEPPER_STOP");
	}
}

int decodeZCommand(volatile unsigned char commands[], int mainLoop) {
	unsigned int i = mainLoop;
	unsigned int j = 0;
	unsigned char tempBuf[10];

	while(commands[i] != '|') {
		if (commands[i] == 'E') {
			if (commands[i + 1] == '1') {
				enableZ();
				} else {
				disableZ();
			}
		}
		
		if (commands[i] == 'D') {
			if (commands[i + 1] == '1') {
				forwardZ();
				} else {
				backwardZ();
			}
		}
		if (commands[i] == 'S') {
			i += 1;
			while(commands[i] != 'S'){
				tempBuf[j] = commands[i];
				i++;
				j++;
			}
			sscanf(tempBuf, "%ld", &zStepper.steps_to_do);
			for (int tempBufCount=0; tempBufCount<10; tempBufCount++){
				tempBuf[tempBufCount] = NULL;
			}
		}
		i++;
	}
	return i;
}
