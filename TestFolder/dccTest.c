//#include "../Atmega8_DCC_signal_generator/DCC_Signalgenerator.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
struct Message1
{
	int value;
	uint8_t byte[3];
};

struct Message2
{
	uint8_t byte[3];
};

struct Message1 msg1;
struct Message2 msg2;

int main(void)
{
	msg1.byte[0] = 122;
	msg1.byte[1] = 144;
	msg1.byte[2] = 166;

	//strncpy(msg2.byte, msg1.byte, 3);
	memcpy(msg2.byte, msg1.byte, 3);
	
	printf("Message2: %d, %d, %d\n", msg2.byte[0], msg2.byte[1], msg2.byte[2]);
	
	return 1;
}