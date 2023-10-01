/*
 * brightness.h
 *
 * Created: 10/18/2022 12:31:28 AM
 *  Author: DR
 */ 


#ifndef BRIGHTNESS_H_
#define BRIGHTNESS_H_

struct Brightness{
	double value;
	volatile unsigned int shouldSend;
};

int decodeBrighntessCommand(volatile unsigned char commands[], int mainLoop);

void enableSendBrightness();
void disableSendBrightness();

void isEnableSendBrightness();

double getBrighnessValue();

#endif /* BRIGHTNESS_H_ */