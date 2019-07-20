/*	Author: mwen004
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#define button1 (~PINB & 0x01)
#define button2 (~PINB & 0x02)

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

unsigned char button = 0x00;

void TimerOn()
{
  TCCR1B = 0x0B;
  OCR1A = 125;
  TIMSK1 = 0x02;
  TCNT1 = 0;

  _avr_timer_cntcurr = _avr_timer_M;
  
  SREG |= 0x80;
}

void TimerOff()
{
  TCCR1B = 0x00;
}

void TimerISR()
{
  TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect)
{
  _avr_timer_cntcurr--;
  if (_avr_timer_cntcurr == 0)
    {
      TimerISR();
      _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M)
{
  _avr_timer_M = M;
  _avr_timer_cntcurr = _avr_timer_M;
}

unsigned char start1 = (0x18);
unsigned char start2 = (0x01);

void Paddle1()
{
	if (button1 && !button2)
	{
		if (start1 < 0xC0)
		{
			start1 = start1<<1;
		}
	}
	else if (!button1 && button2)
	{
		if (start1 > 0x03)
		{
			start1 = start1>>1;
		}
	}
}

unsigned char start3 = (0x18);
unsigned char start4 = (0x80);

void Paddle2()
{
	if (button1 && !button2)
	{
		if (start3 < 0xC0)
		{
			start3 = start3<<1;
		}
	}
	else if (!button1 && button2)
	{
		if (start3 > 0x03)
		{
			start3 = start3>>1;
		}
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;PORTA = 0x00;
    DDRB = 0xFF;PORTB = 0xFF;
	DDRC = 0xFF;PORTC = 0xFF;
	
	
	TimerSet(100);
	TimerOn();
	
	
    /* Insert your solution below */
    while (1) 
    {
		PORTC = ~start1;
		PORTA = start2;
		PORTC = ~start3;
		PORTA = start4;
		Paddle1();
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}
