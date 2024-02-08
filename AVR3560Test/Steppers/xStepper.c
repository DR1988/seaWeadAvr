/*
 * xStepper.c
 *
 * Created: 10/10/2022 2:28:12 AM
 *  Author: DR
 */ 
#include <avr/io.h>
#include <stdio.h>
#include "xStepper.h"

void setupXaxis() {
	DDRF |= (1 << DDF0); //STEPS
	DDRF |= (1 << DDF1); // DIRECTION
	PORTF |= (0 << PF1); // DIRECTION
	DDRD |= (1 << DDD7); //DISABLE
	PORTD |= (1 << PD7); //DISABLE 1 - DISABLE, 0 - ENABLE
}


void enableX() {
	PORTD &= ~(1 << PD7);
}

void disableX() {
	PORTD |= (1 << PD7);
}

void forwardX() {
	PORTF &= ~(1 << PF1);
}

void backwardX() {
	PORTF |= (1 << PF1);
}

void stepX() {
	PORTF ^= (1 << PF0);
	PORTF ^= (1 << PF0);
}

int isXAxisStepperEnable() {
	return ! (PORTD & (1 << PD7));
}

extern struct Stepper xStepper = {0, 0};

void runXStepper() {
	if (xStepper.steps_to_do !=0 && xStepper.done_steps != xStepper.steps_to_do) {
		xStepper.done_steps++;
		stepX();
		} else if (xStepper.steps_to_do != 0 && xStepper.done_steps == xStepper.steps_to_do) {
		xStepper.steps_to_do = 0;
		xStepper.done_steps = 0;
		disableX();
		TransmitString("x_STEPPER_STOP");
	}
}

int decodeXCommand(volatile unsigned char commands[], int mainLoop) {
	unsigned int i = mainLoop;
	unsigned int j = 0;
	unsigned char tempBuf[10];
	while(commands[i] != '|') {
		if (commands[i] == 'E') {
			if (commands[i + 1] == '1') {
				enableX();
				} else {
				disableX();
			}
		}
	
		if (commands[i] == 'D') {
			if (commands[i + 1] == '1') {
				forwardX();
				} else {
				backwardX();
			}
		}
		if (commands[i] == 'S') {
			i += 1;
			while(commands[i] != 'S'){
				tempBuf[j] = commands[i];
				i++;
				j++;
			}
			sscanf(tempBuf, "%ld", &xStepper.steps_to_do);
			for (int tempBufCount=0; tempBufCount<10; tempBufCount++){
				tempBuf[tempBufCount] = NULL;
			}
		}
		i++;
	}
	
	return i;
}