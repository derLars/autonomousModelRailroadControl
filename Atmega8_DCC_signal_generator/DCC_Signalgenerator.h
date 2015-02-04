//#####################################################
//#Saturday, 31.January.2015 made by Lars C. Schwensen#
//#####################################################

//#################################################################
//#This file generates the DCC output signal                      #
//#DEVICE: atmega8                                                #
//#DEVELOPMENT BOARD: OLIMEX P-28                                 #
//#PROGRAMMER: USBPROG (avrispmkII clone)                         #
//#################################################################

//DCC_Signalgenerator.h

#include <stdint.h>

#define ADRESSRANGE 5

typedef struct
{
	void (*synchronizeBits[16])(void);
	void (*startBit)(void);
	void (*speedStepBits[8])(void);
	void (*stopBit)(void);
} ConstantValues;

typedef struct 
{	
	void (*adressBits[8])(void);	
	void (*velocityBits[8])(void); //msb = direction, msb+1 to lsb = velocity
	void (*checksumBits[8])(void);	
} DCC_packet ;

void initialize(void);
void generateSignal(void);
