/*
 * eStepper.c
 *
 * Created: 8/21/2023 11:36:33 PM
 *  Author: DR
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "eStepper.h"

void setupEaxis() {
	DDRC |= (1 << DDC1); //STEPS
	
	DDRC |= (1 << DDC3);//DIRECTION
	PORTC |= (0 << PC3);//DIRECTION
	
	DDRC |= (1 << DDC7);//DISABLE
	PORTC |= (1 << PC7);//DISABLE  1 - DISABLE, 0 - ENABLE
}


void enableE() {
	PORTC &= ~(1 << PC7);
}

void disableE() {
	PORTC |= (1 << PC7);
}

void forwardE() {
	PORTC &= ~(1 << PC3);
}

void backwardE() {
	PORTC |= (1 << PC3);
}

void stepE() {
	PORTC ^= (1 << DDC1);
	PORTC ^= (1 << DDC1);
}

int isEAxisStepperEnable() {
	return ! (PORTC & (1 << PC7));
}

extern struct Stepper eStepper = {0, 0};

void runEStepper() {
	if (eStepper.steps_to_do !=0 && eStepper.done_steps != eStepper.steps_to_do) {
		eStepper.done_steps++;
		stepE();
		} else if (eStepper.steps_to_do != 0 && eStepper.done_steps == eStepper.steps_to_do) {
		eStepper.steps_to_do = 0;
		eStepper.done_steps = 0;
		disableE();
		TransmitString("e_STEPPER_STOP");
	}
}

int decodeECommand(volatile unsigned char commands[], int mainLoop) {
	unsigned int i = mainLoop;
	unsigned int j = 0;
	unsigned char tempBuf[10];
	while(commands[i] != '|') {
		if (commands[i] == 'E') {
			if (commands[i + 1] == '1') {
				enableE();
				} else {
				disableE();
			}
		}
		
		if (commands[i] == 'D') {
			if (commands[i + 1] == '1') {
				forwardE();
				} else {
				backwardE();
			}
		}
		if (commands[i] == 'S') {
			i += 1;
			while(commands[i] != 'S'){
				tempBuf[j] = commands[i];
				i++;
				j++;
			}
			sscanf(tempBuf, "%ld", &eStepper.steps_to_do);
			for (int tempBufCount=0; tempBufCount<10; tempBufCount++){
				tempBuf[tempBufCount] = NULL;
			}
		}
		i++;
	}
	return i;
}
