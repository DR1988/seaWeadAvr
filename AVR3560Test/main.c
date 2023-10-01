/*
 * AVR3560Test.c
 *
 * Created: 8/14/2022 8:51:19 PM
 * Author : DR
 */ 
#define F_CPU 16000000UL 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "UART.h"
#include "PWMinit.h"

#define UART_data_in_length 45

struct UARTData {
	volatile unsigned char data_in[UART_data_in_length];
	volatile unsigned char data_out[8];
	volatile unsigned char dataCount;
	volatile unsigned char sendingTrue;
};

volatile struct UARTData UART0 = {.dataCount = 0, .sendingTrue = 0};
	
void cleanUart() {
	for (int i = 0; i < UART_data_in_length; i++) {
		UART0.data_in[i] = NULL;
	}
}

	
void decodeCommands(volatile unsigned char commands[])
{
	unsigned int i = 0;
	// xE1D1S20S|
	
	//TransmitString(commands);
	//TransmitUART0(commands[0]);
	while(commands[i] != '\n') {
		
		if (commands[i] == 'x') {
			//PORTB ^= (1 << PB7);
			i = decodeXCommand(commands, i);
		}
		if (commands[i] == 'y') {
			//TransmitUART0(commands[i]);
			i = decodeYCommand(commands, i);
		}
		if (commands[i] == 'z') {
			//TransmitUART0(commands[i]);
			i = decodeZCommand(commands, i);
		}
				
		if (commands[i] == 'e') {
			//TransmitUART0(commands[i]);
			i = decodeECommand(commands, i);
		}
		
		if (commands[i] == 'b') {
			//TransmitUART0(commands[i]);
			//TransmitString(commands);
			i = decodeBrighntessCommand(commands, i);
		}
		
		// co2 valve decode commands
		if (commands[i] == 'c') {
			//TransmitUART0(commands[i]);
			i = decodeCO2Command(commands, i);
		}
		
		// purge valve decode commands
		if (commands[i] == 'p') {
			//TransmitUART0(commands[i]);
			i = decodePurgeCommand(commands, i);
		}
		// stop command from control program
		i++;
	}
}

void setup() {
	//DDRH |= (1 << DDH3) | (1 << DDH4) | (1 << DDH5) | (1 << DDH6);
	//PORTH |= (0 << DDH3) | (0 << DDH4) | (0 << DDH5) | (0 << DDH6);
	
	
	//DDRE |= (1 << DDE3);
	
	TCCR0B |= (1 << CS00) | (1 << CS01) | (0 << CS02);
	TIMSK0 |= (1 << TOIE0);
	
	
	//TCCR4A |= (1 << WGM41) | (0 << WGM40) | (1 << COM4C1);
	//TCCR4B |= (1 << WGM43) | (1 << WGM42) | (1 << CS42);
	//ICR4 = 62;
	//OCR4C = 3;
	//
	//DDRH |= (1 << DDH5);
	
	InitializePWM_4C(1000, 0);
	
	setupXaxis();
	setupYaxis();
	setupZaxis();
	setupEaxis();
	
	DDRB |= (1 << DDB7); //GREEN LED
	//PORTB |= (1 << PB7);
	
	//cleanUart();
	
}

int main(void)
{
    /* Replace with your application code */
	setup();
	sei();
	enableY();
	InitializeUART0(9600, 0, 8, 0, 0);
	
    while (1) 
    {
    }
}

int step = 0;
int divider = 0;
int counterValue = 400;
int connected = 0;
ISR(TIMER0_OVF_vect) {
	
	divider++;
	if (divider == counterValue) {
		divider=0;
		//PORTB ^= (1 << PB7);
		if (connected == 0) {
			connected = 1;
			TransmitString("CONNECTED");
		}
	}

		
	if(isXAxisStepperEnable()) {
		runXStepper();
	}
	if(isYAxisStepperEnable()) {
		runYStepper();
	}
	if(isZAxisStepperEnable()) {
		runZStepper();
	}
	if(isEAxisStepperEnable()) {
		runEStepper();
	}



	if (isEnableSendBrightness()) {
		// send_int_Uart(getBrighnessValue());
		//send_int_Uart(getBrighnessValue());
		//send_double_Uart(getBrighnessValue());
		//setPwm(getBrighnessValue());
		//disableSendBrightness();
		//setPwm(getBrighnessValue());
	}
}


ISR (USART0_RX_vect)
{
	//char ReceivedByte;
	//ReceivedByte = UDR0;
	//if (ReceivedByte == '2') {
		//PORTB ^= (1 << PB7);
		//stepZ();
	//}
	//UDR0 = ReceivedByte;
	
	
	UART0.data_in[UART0.dataCount] = UDR0;
	if(UART0.data_in[UART0.dataCount] == '\n') {
		UART0.dataCount = 0;
		//PORTB ^= (1 << PB7);
		decodeCommands(UART0.data_in);
		//TransmitString(UART0.data_in);
	} else {
		if(++UART0.dataCount >= UART_data_in_length){
			UART0.dataCount = 0;
		}
	}
	

}
