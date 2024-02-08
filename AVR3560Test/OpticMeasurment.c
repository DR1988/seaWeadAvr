/*
 * OpticMeasurment.c
 *
 * Created: 10/3/2023 12:10:28 PM
 *  Author: DR
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "OpticMeasurment.h"

void openOpticMeasurment() {
	DDRB |= (1 << DDB0);
	PORTB |= (1 << PB0);
}

void closeOpticMeasurment() {
	PORTB &= ~(1 << PB0);
}

int decodeOpticMeasurmentCommand(volatile unsigned char commands[], int mainLoop) {
	unsigned int i = mainLoop;
	
	while(commands[i] != '|') {
		if (commands[i] == 'O') {
			openOpticMeasurment();
			} else if (commands[i] == 'C') {
			closeOpticMeasurment();
		}
		i++;
	}
	return i;
}