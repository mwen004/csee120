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

  unsigned char fuelLevel = 0x00;
  unsigned char fuelLight = 0x00;
  unsigned char keyIn = 0x00;
  unsigned char driverIn = 0x00;
  unsigned char seatbeltIn = 0x00;

    /* Insert your solution below */
    while (1)
    {
      fuelLevel = PINA & 0x0F;
      keyIn = PINA & (1<<4);
      driverIn = PINA & (1<<5);
      seatbeltIn = PINA & (1<<6);
      
      if (fuelLevel == 1||fuelLevel==2)
	{
	  fuelLight = 0x20;
	}
      if (fuelLevel == 3||fuelLevel==4)
	{
	  fuelLight = 0x30;
	}
      if (fuelLevel == 5||fuelLevel==6)
	{
	  fuelLight = 0x38;
	}
      if (fuelLevel == 7||fuelLevel==8||fuelLevel==9)
	{
	  fuelLight = 0x3C;
	}
      if (fuelLevel == 10||fuelLevel==11||fuelLevel==12)
	{
	  fuelLight = 0x3E;
	}
      if (fuelLevel == 13||fuelLevel==14||fuelLevel==15)
	{
	  fuelLight = 0x3F;
	}

      if(fuelLevel <=4)
	{
	  fuelLight = fuelLight|(1<<6);
	}
      if(keyIn != 0 && driverIn != 0 && !seatbeltIn)
	{
	  fuelLight = fuelLight|(1<<7);
	}
      PORTC = fuelLight;
    }
    return 1;
}
