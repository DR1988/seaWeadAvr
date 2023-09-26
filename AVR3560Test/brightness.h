/*
 * brightness.h
 *
 * Created: 10/18/2022 12:31:28 AM
 *  Author: DR
 */ 


#ifndef BRIGHTNESS_H_
#define BRIGHTNESS_H_

struct Brightness{
	volatile unsigned int value;
	volatile unsigned int shouldSend;
};

int decodeBrighntessCommand(volatile unsigned char commands[], int mainLoop);

void enableSendBrightness();
void disableSendBrightness();

void isEnableSendBrightness();

void getBrighnessValue();

#endif /* BRIGHTNESS_H_ */