/*
 * valveCO2.h
 *
 * Created: 8/22/2023 1:08:31 AM
 *  Author: DR
 */ 


#ifndef VALVECO2_H_
#define VALVECO2_H_

void openCO2Valve();
void closeCO2Valve();
int decodeCO2Command(volatile unsigned char commands[], int mainLoop);


#endif /* VALVECO2_H_ */