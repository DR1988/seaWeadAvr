/*
 * Brighntess.c
 *
 * Created: 10/18/2022 12:32:35 AM
 *  Author: DR
 */ 
#include "brightness.h"
#include <stdio.h>
#include <stdlib.h>

static struct Brightness brightness = {0, 0};

void enableSendBrightness() {
	brightness.shouldSend = 1;
}

void disableSendBrightness() {
	brightness.shouldSend = 0;
}

void isEnableSendBrightness() {
	return brightness.shouldSend == 1;
}

double getBrighnessValue() {
	return brightness.value;
}


int decodeBrighntessCommand(volatile unsigned char commands[], int mainLoop) {
	unsigned int i = mainLoop;
	unsigned int j = 0;
	unsigned char tempBuf[10];
	
	while(commands[i] != '|') {
		if (commands[i] == 'B') {
			i += 1;
			while(commands[i] != 'B'){
				tempBuf[j] = commands[i];
				i++;
				j++;
			}
			double valuess = atof(tempBuf);
			brightness.value = valuess;
			send_double_Uart(getBrighnessValue());
			setPwm(getBrighnessValue());
			
			for (int tempBufCount=0; tempBufCount<10; tempBufCount++){
				tempBuf[tempBufCount] = NULL;
			}
			enableSendBrightness();
		}
		i++;
	}
	 
	return i;
}