//#####################################################
//#Sunday, 01.February.2015 made by Lars C. Schwensen#
//#####################################################

//#################################################################
//#This file handles incomming UART messages                      #
//#DEVICE: atmega8                                                #
//#DEVELOPMENT BOARD: OLIMEX P-28                                 #
//#PROGRAMMER: USBPROG (avrispmkII clone)                         #
//Notice: http://www.mikrocontroller.net/articles/AVR_TWI         #
//#################################################################

//messageDirector.c

#include "../Atmega8_Modules/i2c.h"
#include "../Atmega8_Modules/uart.h"
#include "messageDirector.h"

#include <string.h> 

#include <util/delay.h>
#include <avr/io.h>

struct Message msgToSend;
volatile struct UARTMessage msgToReceive;

void initializeMessageDirector(void)
{
	initUart();
	revokeInterrupt();
	initAsMaster(SLC_FREQUENCY);
}

void handleMessage(void)
{
	//DDRB = 0xff;
	//PORTB = 0x22;

	while(1)
	{		
		receiveMessage(&msgToReceive);
		

		if(msgToReceive.type == 0x00)
		{
			//PORTB = 0b01010101;
			memcpy(msgToSend.byte, msgToReceive.byte, BYTES);
			sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend);
		}	
		else if(msgToReceive.type == 0x01)
		{
		
		//TODO: implement gate control
		/*	
		_delay_ms(500);
		PORTB = msgToReceive.byte[0];
		_delay_ms(500);
		PORTB = msgToReceive.byte[1];
		_delay_ms(500);
		PORTB = msgToReceive.byte[2];
		*/
		}
		
	}	
}