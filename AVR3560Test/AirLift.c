/*
 * AirLift.c
 *
 * Created: 10/3/2023 1:16:20 AM
 *  Author: DR
 */ 
#include <avr/io.h>
#include <stdio.h>
#include "AirLift.h"

void openAirLift() {
	DDRL |= (1 << DDL0);
	PORTL |= (1 << PL0);
}

void closeAitLift() {
	PORTL &= ~(1 << PL0);
}

int decodeAirLiftCommand(volatile unsigned char commands[], int mainLoop) {
	unsigned int i = mainLoop;
	
	while(commands[i] != '|') {
		if (commands[i] == 'O') {
			openAirLift();
			} else if (commands[i] == 'C') {
			closeAitLift();
		}
		i++;	
	}
	return i;
}