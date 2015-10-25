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

#define MS 5000

void initializeMessageDirector(void)
{
	initUart();
	revokeInterrupt();
	initAsMaster(SLC_FREQUENCY);
}

void handleMessage(void)
{
	_delay_ms(2500);
	
	while(1)
	{
		//Velocity 20
		msgToSend.byte[0] = 0x02;
		msgToSend.byte[1] = 0x94;
		msgToSend.byte[2] = 0xA9;
		sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend, 3);
		_delay_ms(MS);

		//Velocity 60
		msgToSend.byte[0] = 0x02;
		msgToSend.byte[1] = 0xBC;
		msgToSend.byte[2] = 0x81;
		sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend, 3);
		_delay_ms(MS);
		
		//Velocity 120
		msgToSend.byte[0] = 0x02;
		msgToSend.byte[1] = 0xF8;
		msgToSend.byte[2] = 0xC5;
		sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend, 3);
		_delay_ms(MS);

		//Velocity 60
		msgToSend.byte[0] = 0x02;
		msgToSend.byte[1] = 0xBC;
		msgToSend.byte[2] = 0x81;
		sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend, 3);
		_delay_ms(MS);

		//Velocity 20
		msgToSend.byte[0] = 0x02;
		msgToSend.byte[1] = 0x94;
		msgToSend.byte[2] = 0xA9;
		sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend, 3);
		_delay_ms(MS);

		//Velocity 0
		msgToSend.byte[0] = 0x02;
		msgToSend.byte[1] = 0x00;
		msgToSend.byte[2] = 0x3D;
		sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend, 3);
		_delay_ms(MS);


		//Velocity -20
		msgToSend.byte[0] = 0x02;
		msgToSend.byte[1] = 0x14;
		msgToSend.byte[2] = 0x29;
		sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend, 3);
		_delay_ms(MS);

		//Velocity -60
		msgToSend.byte[0] = 0x02;
		msgToSend.byte[1] = 0x3C;
		msgToSend.byte[2] = 0x01;
		sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend, 3);
		_delay_ms(MS);
		
		//Velocity -120
		msgToSend.byte[0] = 0x02;
		msgToSend.byte[1] = 0x78;
		msgToSend.byte[2] = 0x45;
		sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend, 3);
		_delay_ms(MS);

		//Velocity -60
		msgToSend.byte[0] = 0x02;
		msgToSend.byte[1] = 0x3C;
		msgToSend.byte[2] = 0x01;
		sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend, 3);
		_delay_ms(MS);

		//Velocity -20
		msgToSend.byte[0] = 0x02;
		msgToSend.byte[1] = 0x14;
		msgToSend.byte[2] = 0x29;
		sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend, 3);
		_delay_ms(MS);

		//Velocity 0
		msgToSend.byte[0] = 0x02;
		msgToSend.byte[1] = 0x00;
		msgToSend.byte[2] = 0x3D;
		sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend, 3);
		_delay_ms(MS);
	}


	//Gate test! Sends commands to GateController 2 and 3
	// while(1)
	// {				
	// 	/*
	// 	msgToSend.byte[0] = GATE1_RIGHT;
	// 	sendAsMaster(CONTROLLER1, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	msgToSend.byte[0] = GATE2_RIGHT;
	// 	sendAsMaster(CONTROLLER1, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	msgToSend.byte[0] = GATE3_RIGHT;
	// 	sendAsMaster(CONTROLLER1, msgToSend, 1);
	// 	_delay_ms(MS);
	// 	*/
	// 	msgToSend.byte[0] = GATE4_RIGHT;
	// 	sendAsMaster(CONTROLLER2, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	msgToSend.byte[0] = GATE5_RIGHT;
	// 	sendAsMaster(CONTROLLER2, msgToSend, 1);
	// 	_delay_ms(MS);
		
	// 	msgToSend.byte[0] = GATE6_RIGHT;
	// 	sendAsMaster(CONTROLLER3, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	msgToSend.byte[0] = GATE7_RIGHT;
	// 	sendAsMaster(CONTROLLER3, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	msgToSend.byte[0] = GATE8_RIGHT;
	// 	sendAsMaster(CONTROLLER3, msgToSend, 1);
	// 	_delay_ms(MS);
		
	// 	msgToSend.byte[0] = GATE9_RIGHT;
	// 	sendAsMaster(CONTROLLER3, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	msgToSend.byte[0] = GATE10_RIGHT;
	// 	sendAsMaster(CONTROLLER3, msgToSend, 1);
	// 	_delay_ms(MS);
		
	// 	msgToSend.byte[0] = GATE11_RIGHT;
	// 	sendAsMaster(CONTROLLER3, msgToSend, 1);
	// 	_delay_ms(MS);

		
	// 	msgToSend.byte[0] = GATE1_LEFT;
	// 	sendAsMaster(CONTROLLER1, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	msgToSend.byte[0] = GATE2_LEFT;
	// 	sendAsMaster(CONTROLLER1, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	msgToSend.byte[0] = GATE3_LEFT;
	// 	sendAsMaster(CONTROLLER1, msgToSend, 1);
	// 	_delay_ms(MS);
		
	// 	msgToSend.byte[0] = GATE4_LEFT;
	// 	sendAsMaster(CONTROLLER2, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	msgToSend.byte[0] = GATE5_LEFT;
	// 	sendAsMaster(CONTROLLER2, msgToSend, 1);
	// 	_delay_ms(MS);
		
	// 	msgToSend.byte[0] = GATE6_LEFT;
	// 	sendAsMaster(CONTROLLER3, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	msgToSend.byte[0] = GATE7_LEFT;
	// 	sendAsMaster(CONTROLLER3, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	msgToSend.byte[0] = GATE8_LEFT;
	// 	sendAsMaster(CONTROLLER3, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	msgToSend.byte[0] = GATE9_LEFT;
	// 	sendAsMaster(CONTROLLER3, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	msgToSend.byte[0] = GATE10_LEFT;
	// 	sendAsMaster(CONTROLLER3, msgToSend, 1);
	// 	_delay_ms(MS);
		
	// 	msgToSend.byte[0] = GATE11_LEFT;
	// 	sendAsMaster(CONTROLLER3, msgToSend, 1);
	// 	_delay_ms(MS);

	// 	/*
	// 	receiveMessage(&msgToReceive);
		

	// 	if(msgToReceive.type == 0x00)
	// 	{
	// 		//PORTB = 0b01010101;
	// 		memcpy(msgToSend.byte, msgToReceive.byte, BYTES);
	// 		sendAsMasterWithInterrupt(SIGNALGENERATORADRESS, msgToSend);
	// 	}	
	// 	else if(msgToReceive.type == 0x01)
	// 	{
		
		
	// 	}
	// 	*/
	// }	
}