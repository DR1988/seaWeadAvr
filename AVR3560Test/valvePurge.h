/*
 * valvlePurge.h
 *
 * Created: 8/22/2023 1:10:31 AM
 *  Author: DR
 */ 


#ifndef VALVLEPURGE_H_
#define VALVLEPURGE_H_


void openPurgeValve();
void closePurgeValve();
int decodePurgeCommand(volatile unsigned char commands[], int mainLoop);

#endif /* VALVLEPURGE_H_ */