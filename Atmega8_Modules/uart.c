//##################################################
//#Friday, 09.Januar.2014 made by Lars C. Schwensen#
//##################################################

//#################################################################
//#This file handles the UART functionality                       #
//#DEVICE: atmega8                                                #
//#DEVELOPMENT BOARD: OLIMEX P-28                                 #
//#PROGRAMMER: USBPROG (avrispmkII clone)                         #
//#################################################################

//uart.c

#include "uart.h"

#include <avr/io.h>

#include <util/setbaud.h>
#include <util/delay.h>

void initUart()
{
	UBRRH = UBRR_VALUE >> 8;
	UBRRL = UBRR_VALUE & 0xFF;
 
	UCSRB = (1 << RXCIE) | (1 << TXCIE) | (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
}

void sendChar(uint8_t character)
{
	while (!(UCSRA & (1<<UDRE)));
	UDR = character;
}

uint8_t receiveChar()
{
	while (!(UCSRA & (1<<RXC)));
	return UDR; 
}

void receiveMessage(volatile struct UARTMessage *msg)
{
	msg->type = receiveChar();
	msg->byte[0] = receiveChar();
	msg->byte[1] = receiveChar();
	msg->byte[2] = receiveChar();	
}