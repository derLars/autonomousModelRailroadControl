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

struct Message msgToSend;
volatile struct UARTMessage msgToReceive;

void initializeMessageDirector(void)
{
	//initUart();
	revokeInterrupt();
	initAsMaster(SLC_FREQUENCY);
}

void handleMessage(void)
{
	while(1)
	{
		//receiveMessage(&msgToReceive);
		msgToReceive.type = 0x00;
		msgToReceive.byte[0] = 0x01;
		msgToReceive.byte[1] = 0b10101010;
		msgToReceive.byte[2] = 0b00110011;

		_delay_ms(5000);

		if(msgToReceive.type == 0x00)
		{
			memcpy(msgToSend.byte, msgToReceive.byte, BYTES);
			sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend);
		}	

		msgToReceive.type = 0x00;
		msgToReceive.byte[0] = 0x02;
		msgToReceive.byte[1] = 0b10001111;
		msgToReceive.byte[2] = 0b11110011;

		_delay_ms(5000);

		if(msgToReceive.type == 0x00)
		{
			memcpy(msgToSend.byte, msgToReceive.byte, BYTES);
			sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend);
		}	

		msgToReceive.type = 0x00;
		msgToReceive.byte[0] = 0x03;
		msgToReceive.byte[1] = 0b00110011;
		msgToReceive.byte[2] = 0b11101110;

		_delay_ms(5000);

		if(msgToReceive.type == 0x00)
		{
			memcpy(msgToSend.byte, msgToReceive.byte, BYTES);
			sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend);
		}	
	}	
}