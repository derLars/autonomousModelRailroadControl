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

void initializeMessageDirector(void);
void handleMessage(void);