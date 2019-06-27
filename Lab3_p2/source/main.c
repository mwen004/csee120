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

int main(void) {
    /* Insert DDR and PORT initializations */
  DDRA = 0x00; PORTA = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;

  unsigned char gasLevel = 0x00;
  unsigned char gasLight = 0x00;

    /* Insert your solution below */
    while (1)
    {
      gasLevel = PINA & 0x0F;//masks PINA to A0-A3
      if (gasLevel == 1||gasLevel ==2)
	{
	  gasLight = 0x20;
	}
      else if(gasLevel == 3||gasLevel==4)
	{
	  gasLight = 0x30;
	}
      else if(gasLevel == 5||gasLevel ==6)
	{
	  gasLight = 0x38;
	}
      else if(gasLevel ==7||gasLevel==8||gasLevel==9)
	{
	  gasLight = 0x3C;
	}
      else if(gasLevel ==10||gasLevel==11||gasLevel==12)
	{
	  gasLight = 0x3E;
	}
      else if(gasLevel== 13||gasLevel==14||gasLevel==15)
	{
	  gasLight = 0x3F;
	}
      if(gasLevel<=4)
	{
	  gasLight = gasLight|(1<<6);
	}
      PORTC = gasLight;

    }
    return 1;
}
