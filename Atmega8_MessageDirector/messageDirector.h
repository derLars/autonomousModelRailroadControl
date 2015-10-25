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

//messageDirector.h

#define CONTROLLER1 	0x24
#define CONTROLLER2 	0x28
#define CONTROLLER3		0x32

#define GATE1_RIGHT 	0b00100001
#define GATE1_LEFT	 	0b00100010

#define GATE2_RIGHT		0b00100011
#define GATE2_LEFT		0b00100100

#define GATE3_RIGHT		0b00100101
#define GATE3_LEFT		0b00100110


#define GATE4_RIGHT 	0b01000001
#define GATE4_LEFT	 	0b01000010

#define GATE5_RIGHT		0b01000011
#define GATE5_LEFT		0b01000100


#define GATE6_RIGHT 	0b10000001
#define GATE6_LEFT	 	0b10000010

#define GATE7_RIGHT		0b10000011
#define GATE7_LEFT		0b10000100

#define GATE8_RIGHT		0b10000101
#define GATE8_LEFT		0b10000110

#define GATE9_RIGHT 	0b10000111
#define GATE9_LEFT 		0b10001000

#define GATE10_RIGHT 	0b10001001
#define GATE10_LEFT 	0b10001010

#define GATE11_RIGHT 	0b10001011
#define GATE11_LEFT 	0b10001100



void initializeMessageDirector(void);
void handleMessage(void);