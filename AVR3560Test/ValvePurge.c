/*
 * ValvePurge.c
 *
 * Created: 8/22/2023 1:14:05 AM
 *  Author: DR
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "valvePurge.h"


void openPurgeValve() {
	PORTB |= (1 << PB4);
	DDRB |= (1 << DDB4);
}

void closePurgeValve() {
	PORTB &= ~(1 << PB4);
}

int decodePurgeCommand(volatile unsigned char commands[], int mainLoop) {
	unsigned int i = mainLoop;
	while(commands[i] != '|') {
		if (commands[i] == 'O') {
			openPurgeValve();
		} else if (commands[i] == 'C') {
			closePurgeValve();
		}
		i++;
	}
	return i;
}