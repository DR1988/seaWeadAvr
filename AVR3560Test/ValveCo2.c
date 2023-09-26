/*
 * ValveCo2.c
 *
 * Created: 8/22/2023 1:13:37 AM
 *  Author: DR
 */ 


#include <avr/io.h>
#include <stdio.h>
#include "valveCO2.h"

void openCO2Valve() {
	PORTH |= (1 << PH6);
	DDRH |= (1 << DDH6);
}

void closeCO2Valve() {
	PORTH &= ~(1 << PH6);
}

int decodeCO2Command(volatile unsigned char commands[], int mainLoop) {
	unsigned int i = mainLoop;
	while(commands[i] != '|') {
		if (commands[i] == 'O') {
			openCO2Valve();
			} else if (commands[i] == 'C') {
			closeCO2Valve();
		}
		i++;
	}
	return i;
}
