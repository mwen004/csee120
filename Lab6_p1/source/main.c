/*	Author: mwen004
 *  Partner(s) Name: Mokane
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

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

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

enum States {Init,SM_1,SM_2,SM_3} state;
void Tick()
{
	switch(state)
	{
		case Init:
		state = SM_1;
		break;
		
		case SM_1:
		state = SM_2;
		break;
		
		case SM_2:
		state = SM_3;
		break;
		
		case SM_3:
		state = SM_1;
		break;
		
		default: state = Init;
		
	}
	
	switch(state)
	{
		case SM_1:
		PORTB = 0x01;
		break;
		
		case SM_2:
		PORTB = 0x02;
		break;
		
		case SM_3:
		PORTB = 0x04;
		break;
		
		case Init:
		break;
	}
}

void main() {
    /* Insert DDR and PORT initializations */
  DDRB = 0xFF; PORTB = 0x00;
  TimerSet(150);
  TimerOn();

	state = Init;
    /* Insert your solution below */
    while (1) {
	Tick();
      while(!TimerFlag);
      TimerFlag = 0;
    }
}
