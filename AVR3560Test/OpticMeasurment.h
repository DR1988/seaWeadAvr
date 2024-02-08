/*
 * OpticMeasurment.h
 *
 * Created: 10/3/2023 12:09:42 PM
 *  Author: DR
 */ 


#ifndef OPTICMEASURMENT_H_
#define OPTICMEASURMENT_H_

void openOpticMeasurment();

void closeOpticMeasurment();

int decodeOpticMeasurmentCommand(volatile unsigned char commands[], int mainLoop);




#endif /* OPTICMEASURMENT_H_ */