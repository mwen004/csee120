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

    /* Insert your solution below */
  DDRA = 0x00; PORTA = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;

  unsigned char cntavail = 0;

    /* Insert your solution below */
    while (1) {
      if (PINA & 0x01){
	cntavail++;
      }
      if (PINA & 0x02){
	cntavail++;
      }
      if (PINA & 0x04){
	cntavail++;
      }
      if (PINA & 0x08){
	cntavail++;
      }
      
      cntavail = 4 - cntavail;
      if (cntavail==0){
	PORTC=0x80;
      }
      else{
	PORTC = cntavail;
      }
      cntavail = 0;
    }
    return 1;
}
