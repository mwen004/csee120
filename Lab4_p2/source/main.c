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
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{SM_START,Wait, INCR, DECR, Wait2, SM_RESET} state;

void Tick()
{
  switch(state)
    {
    case SM_START:
      PORTC = 0x07;
      state = Wait;
      break;

    case Wait:
      if ((PINA & 0x03)==0x03)
	{
	  state = Wait;
	}
      else if ((PINA & 0x01) == 0x01)
	{
	  state = INCR;
	}
      else if ((PINA &  0x02)== 0x02)
	{
	  state = DECR;
	}
      else if (PINA == 0x00)
	{
	  state = SM_RESET;
	}
      break;

    case INCR:
      state = Wait2;
      break;

    case DECR:
      state = Wait2;
      break;

    case Wait2:
      if(PINA == 0x00)
	{
	  state = SM_RESET;
	}
      else if(PINA != 0x03)
	{
	  state = Wait2;
	}
      else
	{
	  state = Wait;
	}
      break;

    case SM_RESET:
      if(PINA == 0x00)
	{
	  state = SM_RESET;
	}
      else if(PINA != 0x03)
	{
	  state = Wait2;
	}
      else
	{
	  state = Wait;
	}
      break;

    default: state = SM_START;
    }

  switch (state)
    {
    case SM_START:
      PORTC = 0x07;
      break;

    case INCR:
      PORTC = PORTC + 1;
      break;

    case DECR:
      PORTC = PORTC - 1;
      break;

    case SM_RESET:
      PORTC = 0x00;
      break;

    case Wait:
      break;

    case Wait2:
      break;
    }
}


int main(void) 
{
    /* Insert DDR and PORT initializations */
  DDRA = 0x00; PORTA = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;

  state = SM_START;
    /* Insert your solution below */
    while (1) {
      Tick();
    }
    return 1;
}
