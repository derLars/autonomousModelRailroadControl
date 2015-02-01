//######################################################
//#Wednesday, 28.January.2015 made by Lars C. Schwensen#
//######################################################

//#################################################################
//#This is the hardware abstraction layer of the DCC protocol     #
//#DEVICE: atmega8                                                #
//#DEVELOPMENT BOARD: OLIMEX P-28                                 #
//#PROGRAMMER: USBPROG (avrispmkII clone)                         #
//#################################################################

//DCC_hal.c
#include "DCC_hal.h"
#include <avr/interrupt.h>

uint8_t i;

#ifndef test
void initGPIO(void)
{
	DDRB |= (1<<PB0) | (1<<PB1);
	PORTB = 0x00;
}
#endif

void zeroLong(void)
{
	PORTB = (1<<PB0);
	for(i=0;i<110;i++);
	sei();
	PORTB = (1<<PB1);
	for(i=0;i<110;i++);	
	cli();
}

void zero(void)
{
	PORTB = (1<<PB0);
	for(i=0;i<88;i++);
	PORTB = (1<<PB1);
	for(i=0;i<88;i++);	
}

void one(void)
{
	PORTB = (1<<PB0);
	for(i=0;i<45;i++);
	PORTB = (1<<PB1);
	for(i=0;i<45;i++);	
}