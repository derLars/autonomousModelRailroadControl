//######################################################
//#Wednesday, 28.January.2015 made by Lars C. Schwensen#
//######################################################

//#################################################################
//#This is the hardware abstraction layer of the DCC protocol     #
//#DEVICE: atmega8                                                #
//#DEVELOPMENT BOARD: OLIMEX P-28                                 #
//#PROGRAMMER: USBPROG (avrispmkII clone)                         #
//#################################################################

//DCC_hal.h

#include "stdint.h"

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

void initGPIO(void);

void zero(void);
void zeroLong(void);

void one(void);
