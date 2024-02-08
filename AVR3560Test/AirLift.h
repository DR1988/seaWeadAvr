/*
 * AirLift.h
 *
 * Created: 10/3/2023 1:14:50 AM
 *  Author: DR
 */ 


#ifndef AIRLIFT_H_
#define AIRLIFT_H_

void openAirLift();

void closeAitLift();

int decodeAirLiftCommand(volatile unsigned char commands[], int mainLoop);

#endif /* AIRLIFT_H_ */