//#####################################################
//#Saturday, 31.January.2015 made by Lars C. Schwensen#
//#####################################################

//#################################################################
//#This file generates the DCC output signal                      #
//#DEVICE: atmega8                                                #
//#DEVELOPMENT BOARD: OLIMEX P-28                                 #
//#PROGRAMMER: USBPROG (avrispmkII clone)                         #
//#################################################################

//DCC_Signalgenerator.c

#include "DCC_hal.h"
#include "DCC_Signalgenerator.h"
#include "../Atmega8_Modules/i2c.h"

#include <avr/interrupt.h>

volatile struct Message msgToReceive;
volatile DCC_packet train[ADRESSRANGE];
ConstantValues constantValues;

void decode(void);

ISR(INT0_vect)       
{   	
   	cli();
  	switch(checkRequest())
  	{
  		case REQUEST_TO_READ:
  			receiveAsSlave(&msgToReceive);
  			decode();
  			break;
  		default:

  			break;
  	}    	
   	sei();
}

void decode(void)
{
	uint8_t i;
	for(i=0; i<8;i++)
	{
		train[msgToReceive.byte[0]].adressBits[i]   = msgToReceive.byte[0] & (1<<i) ? (void*)one : (void*)zero;
		train[msgToReceive.byte[0]].velocityBits[i] = msgToReceive.byte[1] & (1<<i) ? (void*)one : (void*)zero;
		train[msgToReceive.byte[0]].checksumBits[i] = msgToReceive.byte[2] & (1<<i) ? (void*)one : (void*)zero;
	}	
}

void initialize(void)
{
	uint8_t i,j;
	
	initGPIO();

	for(i=0; i<16;i++)
	{
		constantValues.synchronizeBits[i] = (void*)one;

	}	

	for(i=0; i<6;i++)
	{
		constantValues.speedStepBits[i] = (void*)one;
	}


	constantValues.speedStepBits[6] = (void*)zero;
	constantValues.speedStepBits[7] = (void*)zero;

	constantValues.startBit = (void*)zeroLong;
	constantValues.stopBit = (void*)one;

	for(i=0; i<ADRESSRANGE; i++)
	{		
		for(j=0; j<8; j++)
		{
			
			train[i].adressBits[j] = i & (1<<j) ? (void*)one : (void*)zero;						
			train[i].velocityBits[j] = (void*)zero;
			train[i].checksumBits[j] = (void*)zero;
		}				
	}
}

void generateSignal(void)
{
	int8_t i,j;
	while(1)
	{
		for(i=0; i<ADRESSRANGE; i++)
		{
			for(j=15; j>=0; j--)
			{
				constantValues.synchronizeBits[j]();
			}
			constantValues.startBit();

			for(j=7; j>=0; j--)
			{
				train[i].adressBits[j]();
			}

			constantValues.startBit();

			for(j=7; j>=0; j--)
			{
				constantValues.speedStepBits[j]();
			}

			constantValues.startBit();

			for(j=7; j>=0; j--)
			{
				train[i].velocityBits[j]();
			}

			constantValues.startBit();

			for(j=7; j>=0; j--)
			{
				train[i].checksumBits[j]();
			}

			constantValues.stopBit();
		}
	}	
}