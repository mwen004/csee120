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

unsigned char GetBit(unsigned char x, unsigned char k)
{
  return((x & (0x01<<k))!=0);
}
int main(void) {
    /* Insert DDR and PORT initializations */
  DDRA = 0x00; PORTA = 0xFF;
  DDRB = 0x00; PORTB = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;

  unsigned char bitcounter = 0x00;
  unsigned char outcounter = 0x00;
    /* Insert your solution below */
    while (1) {
      while (bitcounter < 8)
	{
	  if (GetBit(PINA,bitcounter))
	    {
	      outcounter++;
	    }
	  if (GetBit(PINB,bitcounter))
	    {
	      outcounter++;
	    }
	  bitcounter++;
    }
      PORTC = outcounter;
      bitcounter = 0x00;
      outcounter = 0x00;
    }
    return 1;
}
