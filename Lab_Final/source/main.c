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

unsigned char button1 = 0x00;
unsigned char button2 = 0x00;
unsigned char button3 = 0x00;
unsigned char button4 = 0x00;
unsigned char button5 = 0x00;
unsigned short cnt1 = 0x00;
unsigned short cnt2 = 0x00;
unsigned short p1_pos = 0x00;
unsigned short p2_pos = 0x00;

enum States1 {HOLD1,INCR1,DECR1} State1;
void P1_Tick()
{
	switch(State1)
	{
		case HOLD1:
		if ((button1 == 0x00) && (button2 == 0x00))
		{
			State1 = HOLD1;
		}
		else if ((button1 == 0x01) && (button2 == 0x00))
		{
			State1 = INCR1;
		}
		else if ((button1 == 0x00) && (button2 == 0x01))
		{
			State1 = DECR1;
		}
		else if ((button1 == 0x01) && (button2 == 0x01))
		{
			State1 = HOLD1;
		}
		break;

		case INCR1:
		if ((p1_pos<6)&&(cnt1<=0))
		{
			p1_pos = p1_pos + 1;
		}
		if ((button1 == 0x00)&&(button2 == 0x00))
		{
			State1 = HOLD1;
			cnt1 = 0;
		}
		else if ((button1 == 0x01)&&(button2 == 0x00))
		{
			cnt1 = cnt1 + 1;
			if (cnt1 >= 200)
			{
				cnt1 = 0;
			}
			State1 = INCR1;
		}
		else if ((button1 == 0x00)&&(button2 == 0x01))
		{
			State1 = DECR1;
			cnt1 = 0;
		}
		else if ((button1 == 0x01)&&(button2 == 0x01))
		{
			State1 = HOLD1;
			cnt1 = 0;
		}
		break;
		
		case DECR1:
		if ((p1_pos>1)&&(cnt1<=0))
		{
			p1_pos = p1_pos - 1;
		}
		if ((button1 == 0x00)&&(button2 == 0x00))
		{
			State1 = HOLD1;
			cnt1 = 0;
		}
		else if ((button1 == 0x00)&&(button2 == 0x01))
		{
			cnt1 = cnt1 + 1;
			State1 = DECR1;
			if (cnt1 >= 200)
			{
				cnt1 = 0;
			}
		}
		else if ((button1 == 0x01)&&(button2 == 0x00))
		{
			State1 = INCR1;
			cnt1 = 0;
		}
		else if ((button1 == 0x01)&&(button2 == 0x01))
		{
			State1 = HOLD1;
			cnt1 = 0;
		}
		break;
	}
}

enum States2 {HOLD2,INCR2,DECR2} State2;
void P2_Tick()
{
	switch(State2)
	{
		case HOLD2:
		if ((button3 == 0x00) && (button4 == 0x00))
		{
			State2 = HOLD2;
		}
		else if ((button3 == 0x01) && (button4 == 0x00))
		{
			State2 = INCR2;
		}
		else if ((button3 == 0x00) && (button4 == 0x01))
		{
			State2 = DECR2;
		}
		else if ((button3 == 0x01) && (button4 == 0x01))
		{
			State2 = HOLD2;
		}
		break;

		case INCR2:
		if ((p2_pos<6)&&(cnt2<=0))
		{
			p2_pos = p2_pos + 1;
		}
		if ((button3 == 0x00)&&(button4 == 0x00))
		{
			State2 = HOLD2;
			cnt2 = 0;
		}
		else if ((button3 == 0x01)&&(button4 == 0x00))
		{
			cnt2 = cnt2 + 1;
			if (cnt2 >= 200)
			{
				cnt2 = 0;
			}
			State2 = INCR2;
		}
		else if ((button3 == 0x00)&&(button4 == 0x01))
		{
			State2 = DECR2;
			cnt2 = 0;
		}
		else if ((button3 == 0x01)&&(button4 == 0x01))
		{
			State2 = HOLD2;
			cnt2 = 0;
		}
		break;
		
		case DECR2:
		if ((p2_pos>1)&&(cnt2<=0))
		{
			p2_pos = p2_pos - 1;
		}
		if ((button3 == 0x00)&&(button4 == 0x00))
		{
			State2 = HOLD2;
			cnt2 = 0;
		}
		else if ((button3 == 0x00)&&(button4 == 0x01))
		{
			cnt2 = cnt2 + 1;
			State2 = DECR2;
			if (cnt2 >= 200)
			{
				cnt2 = 0;
			}
		}
		else if ((button3 == 0x01)&&(button4 == 0x00))
		{
			State2 = INCR2;
			cnt2 = 0;
		}
		else if ((button3 == 0x01)&&(button4 == 0x01))
		{
			State2 = HOLD2;
			cnt2 = 0;
		}
		break;
	}
}

unsigned char col_sel_p1 = 0x00;
unsigned char col_sel_p2 = 0x00;
void Paddle1()
{
	if (p1_pos == 0x01)
	{
		col_sel_p1 = 0xF8;
	}
	else if (p1_pos == 0x02)
	{
		col_sel_p1 = 0xF1;
	}
	else if (p1_pos == 0x03)
	{
		col_sel_p1 = 0xE3;
	}
	else if (p1_pos == 0x04)
	{
		col_sel_p1 = 0xC7;
	}
	else if (p1_pos == 0x05)
	{
		col_sel_p1 = 0x8F;
	}
	else
	{
		col_sel_p1 = 0x1F;
	}
}
void Paddle2()
{
	if (p2_pos == 0x01)
	{
		col_sel_p2 = 0xF8;
	}
	else if (p2_pos == 0x02)
	{
		col_sel_p2 = 0xF1;
	}
	else if (p2_pos == 0x03)
	{
		col_sel_p2 = 0xE3;
	}
	else if (p2_pos == 0x04)
	{
		col_sel_p2 = 0xC7;
	}
	else if (p2_pos == 0x05)
	{
		col_sel_p2 = 0x8F;
	}
	else
	{
		col_sel_p2 = 0x1F;
	}
}

enum States3{U_RIGHT,RIGHT,D_RIGHT,U_LEFT,LEFT,D_LEFT,P1_Score,P2_Score}State3;
unsigned short ballspeed = 0x00;
signed short ball_x = 0x00;
signed short ball_y = 0x00;
unsigned char col_sel_3 = 0xF7;
unsigned char p1score = 0x00;
unsigned char p2score = 0x00;
void ballPhysics()
{
	ballspeed = ballspeed + 1;
	if (ballspeed >= 160)
	{
		ballspeed = 0;
		switch(State3)
		{
			case U_RIGHT:
			if((ball_y == p2_pos + 2) && (ball_x == 6))
			{
				State3 = D_LEFT;
			}
			else if((ball_y == p2_pos) && (ball_x == 6))
			{
				State3 = U_LEFT;
			}
			else if((ball_y == p2_pos + 1) && (ball_x == 6))
			{
				State3 = LEFT;
			}
			else if((abs(ball_y - p2_pos)>=2) && (ball_x == 6))
			{
				State3 = P1_Score;
			}
			else if((ball_y <= 1) && (ball_x >= 2) && (ball_x<=7))
			{
				State3 = D_RIGHT;
			}
			else
			{
				col_sel_3 = ~col_sel_3;
				col_sel_3 = col_sel_3 >> 1;
				col_sel_3 = ~col_sel_3;
				ball_x= ball_x + 1;
				ball_y= ball_y - 1;
			}
			break;
			
			case RIGHT:
			if ((ball_y == p2_pos) && (ball_x == 6))
			{
				State3 = U_LEFT;
			}
			else if ((ball_y == p2_pos + 2) && (ball_x == 6))
			{
				State3 = D_LEFT;
			}
			else if ((ball_y == p2_pos + 1) && (ball_x == 6))
			{
				State3 = LEFT;
			}
			else if ((abs(ball_x - p2_pos)>=3) && (ball_x == 7))
			{
				State3 = P1_Score;
			}
			else
			{
				ball_x = ball_x + 1;
			}
			break;
			
			case D_RIGHT:
			if ((ball_y == p2_pos + 2) && (ball_x == 6))
			{
				State3 = D_LEFT;
			}
			else if ((ball_y == p2_pos) && (ball_x == 6))
			{
				State3 = U_LEFT;
			}
			else if ((ball_y == p2_pos + 1) && (ball_x ==6))
			{
				State3 = LEFT;
			}
			else if ((abs(ball_y - p2_pos)>=2) && (ball_x == 6))
			{
				State3 = P1_Score;
			}
			else if ((ball_y == 8) && (ball_x >= 2) && (ball_x <= 7))
			{
				State3 = U_RIGHT;
			}
			else
			{
				col_sel_3 = ~col_sel_3;
				col_sel_3 = col_sel_3 << 1;
				col_sel_3 = ~col_sel_3;
				ball_x = ball_x + 1;
				ball_y = ball_y + 1;
			}
			break;

			case U_LEFT:
			if ((ball_y == p1_pos + 2) && (ball_x == 1))
			{
				State3 = D_RIGHT;
			}
			else if ((ball_y == p1_pos) && (ball_x == 1))
			{
				State3 = U_RIGHT;
			}
			else if ((ball_y == p1_pos + 1) && (ball_x == 1))
			{
				State3 = RIGHT;
			}
			else if ((abs(ball_y - p1_pos)>=2) && (ball_x == 1))
			{
				State3 = P2_Score;
			}
			else if ((ball_y <= 1) && (ball_x >= 2) && (ball_x <= 7))
			{
				State3 = D_LEFT;
			}
			else
			{
				col_sel_3 = ~col_sel_3;
				col_sel_3 = col_sel_3 >> 1;
				col_sel_3 = ~col_sel_3;
				ball_x = ball_x - 1;
				ball_y = ball_y - 1;
			}
			break;

			case LEFT:
			if ((ball_y == p1_pos) && (ball_x == 1))
			{
				State3 = U_RIGHT;
			}
			else if ((ball_y == p1_pos + 2) && (ball_x == 1))
			{
				State3 = D_RIGHT;
			}
			else if ((ball_y == p1_pos + 1) && (ball_x == 1))
			{
				State3 = RIGHT;
			}
			else if ((abs(ball_y - p1_pos)>=3) && (ball_x == 1))
			{
				State3 = P2_Score;
			}
			else
			{
				ball_x = ball_x - 1;
			}
			break;

			case D_LEFT:
			if ((ball_y == p1_pos + 2) && (ball_x == 1))
			{
				State3 = D_RIGHT;
			}
			else if ((ball_y == p1_pos) && (ball_x == 1))
			{
				State3 = U_RIGHT;
			}
			else if ((ball_y == p1_pos + 1) && (ball_x == 1))
			{
				State3 = RIGHT;
			}
			else if ((abs(ball_y - p1_pos)>=2) && (ball_x == 1))
			{
				State3 = P2_Score;
			}
			else if ((ball_y == 8) && (ball_x >= 2) && (ball_x <= 7))
			{
				State3 = U_LEFT;
			}
			else
			{
				col_sel_3 = ~col_sel_3;
				col_sel_3 = col_sel_3 << 1;
				col_sel_3 = ~col_sel_3;
				ball_x = ball_x - 1;
				ball_y = ball_y + 1;
			}
			break;

			case P1_Score:
			p1score = p1score + 1;
			ball_x = 4;
			ball_y = 4;
			col_sel_3 = 0xF7;
			State3 = LEFT;
			break;

			case P2_Score:
			p2score = p2score + 1;
			ball_x = 4;
			ball_y = 4;
			col_sel_3 = 0xF7;
			State3 = RIGHT;
			break;
		}
	}
}

unsigned short j = 0x00;
int col_array[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
void PortDisplay()
{
	if (j == 0)
	{
		PORTB = col_array[j];
		PORTA = col_sel_p1;
	}
	else if ((j >= 1) && (j < 7))
	{
		if (j == ball_x)
		{
			PORTB = col_array[j];
			PORTA = col_sel_3;
		}
		else
		{
			PORTB = col_array[j];
			PORTA = 0xFF;
		}
	}
	else if (j == 7)
	{
		PORTB = col_array[j];
		PORTA = col_sel_p2;
		j = 0;
		return;
	}
	j = j + 1;
}


int main(void) 
{
    /* Insert DDR and PORT initializations */
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xF0; PORTD = 0x0F;
	TimerSet(1);
	TimerOn();
	State1 = HOLD1;
	State2 = HOLD2;
	State3 = LEFT;
    /* Insert your solution below */
    p1_pos = 3;
    p2_pos = 3;
    ball_x = 4;
    ball_y = 4;
    while (1) 
    {
		button1 = !(PIND & 0x01);
		button2 = !(PIND & 0x02);
		button3 = !(PIND & 0x04);
		button4 = !(PIND & 0x08);
		P1_Tick();
		P2_Tick();
		Paddle1();
		Paddle2();
		PortDisplay();
		ballPhysics();
		while (!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}
