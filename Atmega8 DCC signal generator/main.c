#include "DCC_hal.h"
#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
	initGPIO();

	int i;
	while(1)
	{		
		one();
		zero();
	}
	
	return 0;
}	