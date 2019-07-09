/*/*	Author: mwen004
 *  Partner(s) Name: Moker
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

void ADC_init(){
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE);
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
    
    ADC_init();
    unsigned short Max = 0x11F;
    //unsigned char Min = 0x018;

    
    while (1) {
		unsigned short x = ADC;
		
		if (x >= Max/2){
			PORTB = 0x01;
		}
		else if (x < Max/2){
			PORTB = 0x00;
		}
		
    }
    return 1;
}

//MAX = 0100011111
//MIN = 0000011000
