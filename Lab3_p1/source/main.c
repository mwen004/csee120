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
  DDRB = 0x00; PORTB = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;

  unsigned char bitcounter = 0x00;
  unsigned char outcounter = 0x00;
  unsigned char numOnes = 0x00;
    /* Insert your solution below */
    while (1) {
      PINA = PINA >>1;
      PINB = PINB >>1;
      bitcounter = (PINA & 0x01);
      outcounter = (PINB & 0x01);
      
      if(bitcounter ==0x01){
	numOnes = numOnes + 1;
      }
      if(outcounter ==0x01){
	numOnes = numOnes + 1;
      }
      if (bitcounter==0 && outcounter==0){
	PORTC = numOnes;
      }
      else{
	PORTC = numOnes;
      }
    }
    PORTC = numOnes;
    bitcounter = 0x00;
    outcounter = 0x00;
    numOnes = 0x00;
    return 1;
}
