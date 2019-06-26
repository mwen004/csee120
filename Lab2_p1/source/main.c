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
  DDRB = 0xFF; PORTB = 0x00;

  unsigned char tmpB0 = 0x00;
  unsigned char tmpA0 = 0x00;
  unsigned char tmpA1 = 0x00;

    /* Insert your solution below */
    while (1) {
      tmpA0 = PINA;
      tmpA0 = tmpA0 & 0x01;
      tmpA1 = PINA;
      tmpA1 = tmpA1 & 0x02;
      tmpB0 = tmpA0 && !tmpA1;

      if (tmpB0){
	PORTB = 0x01;
      }
      else{
	PORTB = 0x00;
      }
    }
    return 1;
}
