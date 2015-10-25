
#include "../Atmega8_Modules/i2c.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#define CONTROLLER3


#ifdef CONTROLLER1

#define SLAVEADRESS 		0x24
#define GATE1_RIGHT 	0b00100001
#define GATE1_LEFT	 	0b00100010

#define GATE2_RIGHT		0b00100011
#define GATE2_LEFT		0b00100100

#define GATE3_RIGHT		0b00100101
#define GATE3_LEFT		0b00100110

#define GATE4_RIGHT 	0b11100111
#define GATE4_LEFT 		0b11101000

#define GATE5_RIGHT 	0b11101001
#define GATE5_LEFT 		0b11101010

#define GATE6_RIGHT 	0b11101011
#define GATE6_LEFT 		0b11101100

#endif

#ifdef CONTROLLER2

#define SLAVEADRESS 		0x28
#define GATE1_RIGHT 	0b01000001
#define GATE1_LEFT	 	0b01000010

#define GATE2_RIGHT		0b01000011
#define GATE2_LEFT		0b01000100

#define GATE3_RIGHT		0b11100101
#define GATE3_LEFT		0b11100110

#define GATE4_RIGHT 	0b11100111
#define GATE4_LEFT 		0b11101000

#define GATE5_RIGHT 	0b11101001
#define GATE5_LEFT 		0b11101010

#define GATE6_RIGHT 	0b11101011
#define GATE6_LEFT 		0b11101100

#endif

#ifdef CONTROLLER3

#define SLAVEADRESS 		0x32
#define GATE1_RIGHT 	0b10000001
#define GATE1_LEFT	 	0b10000010

#define GATE2_RIGHT		0b10000011
#define GATE2_LEFT		0b10000100

#define GATE3_RIGHT		0b10000101
#define GATE3_LEFT		0b10000110

#define GATE4_RIGHT 	0b10000111
#define GATE4_LEFT 		0b10001000

#define GATE5_RIGHT 	0b10001001
#define GATE5_LEFT 		0b10001010

#define GATE6_RIGHT 	0b10001011
#define GATE6_LEFT 		0b10001100

#endif


struct Message msgToReceive;

int portb[2];
int portd[2];
int step;

ISR (TIMER1_OVF_vect)  // timer1 overflow interrupt
{
    step = (step + 1) % 2;
    
    PORTB &= ~portb[step];
    PORTD &= ~portd[step];
    portb[step] = 0;
    portd[step] = 0;
}

ISR (TIMER0_OVF_vect)  // timer0 overflow interrupt
{
    step = (step + 1) % 2;
    
    PORTB &= ~portb[step];
    PORTD &= ~portd[step];
    portb[step] = 0;
    portd[step] = 0;
}

void clearTimer(void)
{
	cli();
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	sei();
}

#ifndef CONTROLLER2
int main(void)
{			
	step = 0;
	
	//16 Bit Timer
	//TCCR1A = 0x00;
	
	//TCCR1B = (1 << CS10) | (1 << CS11); //prescaler = 64
	//TCCR1B = (1 << CS11); //prescaler = 8
	//TCCR1B = (1 << CS10); //prescaler = 1
	//TIMSK = (1 << TOIE1); //enable timer1
	
	//8 Bit Timer
	//TCCR0 = (1 << CS00); //prescaler = 1
	//TCCR0 = (1 << CS01); //prescaler = 8
	//TCCR0 = (1 << CS00) | (1 << CS01); //prescaler = 64
	TCCR0 = (1 << CS02) ; //prescaler = 256
	TIMSK = (1 << TOIE0); //enable timer0

	DDRB = 0xff;
	DDRD = 0xff;
	PORTB = 0x00;
	PORTD = 0x00;
	
	initAsSlave(SLAVEADRESS);

	msgToReceive.byte[0] = 0b00000000;
	sei();
	while(1)
	{	
		switch(checkRequest())
  		{
  			case REQUEST_TO_READ:				
  				receiveAsSlave(&msgToReceive);
  				break;
  		
  			default:
  				continue;
 	 			break;
 	 	}	 	 	 	
 	 	
	 	switch (msgToReceive.byte[0])
		{
			case GATE1_RIGHT:				
				PORTB &= ~(1<<PB1);
				PORTB |= (1<<PB0);
				portb[step] |= (1<<PB0);
				break;
			case GATE1_LEFT:				
				PORTB &= ~(1<<PB0);
				PORTB |= (1<<PB1);
				portb[step] |= (1<<PB1);
				break;
			case GATE2_RIGHT:				
				PORTB &= ~(1<<PB3);
				PORTB |= (1<<PB2);
				portb[step] |= (1<<PB2);
				break;
			case GATE2_LEFT:
				PORTB &= ~(1<<PB2);
				PORTB |= (1<<PB3);
				portb[step] |= (1<<PB3);
				break;				
			case GATE3_RIGHT:
				PORTB &= ~(1<<PB5);
				PORTB |= (1<<PB4);
				portb[step] |= (1<<PB4);
				break;
			case GATE3_LEFT:
				PORTB &= ~(1<<PB4);
				PORTB |= (1<<PB5);
				portb[step] |= (1<<PB5);
				break;
			case GATE4_RIGHT:
				PORTD &= ~(1<<PD6);
				PORTD |= (1<<PD7);
				portd[step] |= (1<<PD7);
				break;
			case GATE4_LEFT:
				PORTD &= ~(1<<PD7);
				PORTD |= (1<<PD6);
				portd[step] |= (1<<PD6);
				break;
			case GATE5_RIGHT:
				PORTD &= ~(1<<PD2);
				PORTD |= (1<<PD5);
				portd[step] |= (1<<PD5);
				break;
			case GATE5_LEFT:
				PORTD &= ~(1<<PD5);
				PORTD |= (1<<PD2);
				portd[step] |= (1<<PD2);
				break;
			case GATE6_RIGHT:
				PORTD &= ~(1<<PD0);
				PORTD |= (1<<PD1);
				portd[step] |= (1<<PD1);
				break;
			case GATE6_LEFT:
				PORTD &= ~(1<<PD1);
				PORTD |= (1<<PD0);
				portd[step] |= (1<<PD0);
				break;
			default:
				break;
		}
	}
}

#endif

#ifdef CONTROLLER2
int main(void)
{			
	step = 0;
	
	TCCR1A = 0x00;
	
	//TCCR1B = (1 << CS10) | (1 << CS11); //prescaler = 64
	TCCR1B = (1 << CS11); //prescaler = 8
	TIMSK = (1 << TOIE1);
	
	DDRB = 0xff;
	DDRD = 0xff;
	PORTB = 0x00;
	PORTD = 0x00;
	
	initAsSlave(SLAVEADRESS);

	msgToReceive.byte[0] = 0b00000000;
	sei();
	while(1)
	{	
		switch(checkRequest())
  		{
  			case REQUEST_TO_READ:				
  				receiveAsSlave(&msgToReceive);
  				break;
  		
  			default:
  				continue;
 	 			break;
 	 	}	 	 	 	
 	 	
	 	switch (msgToReceive.byte[0])
		{
			case GATE1_RIGHT:				
				PORTB &= ~(1<<PB2);
				PORTB |= (1<<PB1);
				portb[step] |= (1<<PB1);
				break;
			case GATE1_LEFT:				
				PORTB &= ~(1<<PB1);
				PORTB |= (1<<PB2);
				portb[step] |= (1<<PB2);
				break;
			case GATE2_RIGHT:				
				PORTB &= ~(1<<PB4);
				PORTB |= (1<<PB3);
				portb[step] |= (1<<PB3);
				break;
			case GATE2_LEFT:
				PORTB &= ~(1<<PB3);
				PORTB |= (1<<PB4);
				portb[step] |= (1<<PB4);
				break;				
			case GATE3_RIGHT:				
				break;
			case GATE3_LEFT:				
				break;
			case GATE4_RIGHT:
				break;
			case GATE4_LEFT:
				break;
			case GATE5_RIGHT:
				break;
			case GATE5_LEFT:
				break;
			case GATE6_RIGHT:
				break;
			case GATE6_LEFT:
				break;
			default:
				break;
		}
	}
}

#endif
