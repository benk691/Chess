/*
 * led.c
 *
 * Created: 6/4/2012 1:35:16 PM
 *  Author: Embedded Systems Lab
 */ 

/*
 * led.c
 *
 * Created: 6/4/2012 8:52:21 AM
 *  Author: Embedded Systems Lab
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "ShiftReg.h"

/******** Timer functions ********************************************/
// TimerISR() sets this to 1. C programmer should clear to 0.
volatile unsigned char TimerFlag=0;

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M=1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr=0; // Current internal count of 1ms ticks

void TimerOn()
{
    // AVR timer/counter controller register TCCR0
    TCCR0 = 0x0B;        // bit3bit6=10: CTC mode (clear timer on compare)
                // bit2bit1bit0=011: prescaler /64
                // 00001011: 0x0B
                // SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
                // Thus, TCNT0 register will count at 125,000 ticks/s

    // AVR output compare register OCR0.
    OCR0 = 125;        // Timer interrupt will be generated when TCNT0==OCR0
                // We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
                // So when TCNT0 register equals 125,
                // 1 ms has passed. Thus, we compare to 125.
                // AVR timer interrupt mask register

    TIMSK = 0x02; // bit1: OCIE0 -- enables compare match interrupt

    //Initialize avr counter
    TCNT0=0;

    _avr_timer_cntcurr = _avr_timer_M;
    // TimerISR will be called every _avr_timer_cntcurr milliseconds

    //Enable global interrupts
    SREG |= 0x80; // 0x80: 1000000
}

void TimerOff()
{
    TCCR0 = 0x00; // bit2bit1bit0=000: timer off
}

void TimerISR()
{
    TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER0_COMP_vect)
{
    // CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
    _avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
    if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
        TimerISR(); // Call the ISR that the user uses
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M)
{
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}
/*--------END timer functions ------------------------------------------------*/

struct LED
{
	unsigned char row_i;
	unsigned long data;
};

unsigned char row[ 8 ] =
{
	0x7F,  //0111 1111 
	0xBF,  //1011 1111
	0xDF,  //1101 1111
	0xEF,  //1110 1111
	0xF7,  //1111 0111
	0xFB,  //1111 1011
	0xFD,  //1111 1101
	0xFE,  //1111 1110
};

unsigned long col[ 8 ] =
{
	0x03C0,		//GG BB BB RR
	0x03C0,		//GG BB BB RR
	0x03C0,		//GG BB BB RR
	0x03C0,		//GG BB BB RR
	0x03C0,		//GG BB BB RR
	0x03C0,		//GG BB BB RR
	0x03C0,		//GG BB BB RR
	0x03C0		//GG BB BB RR
};
/*
LED col[ 8 ] =
{
	LED(0, 0x03C0),		//GG BB BB RR
	LED(1, 0x03C0),		//GG BB BB RR
	LED(2, 0x03C0),		//GG BB BB RR
	LED(3, 0x03C0),		//GG BB BB RR
	LED(4, 0x03C0),		//GG BB BB RR
	LED(5, 0x03C0),		//GG BB BB RR
	LED(6, 0x03C0),		//GG BB BB RR
	LED(7, 0x03C0)		//GG BB BB RR
};
*/

void WriteBoard()
{
	SR_RowWrite(0xFF);
	
	for(unsigned char i = 0; i < 8; i++)
	{
		SR_RowWrite(row[i]);
		SR_ColWrite(col[i]);
		while(!TimerFlag);
		TimerFlag = 0;
	}
	
}

int main(void)
{
	SRInit();
	TimerSet(3);
	TimerOn();
	
	//unsigned char max_tick = 4;
	//unsigned char tick = 0;

    while(1)
    {
		col[0] = 0x0BC0;
		col[3] = 0x09C0;
		col[4] = 0x0290;
		
		WriteBoard();
	
    }
}
	/*
		if(tick == 1)
		{
			col[3] = 0x09C0;
		}
		
		else if(tick == 2)
		{
			col[4] = 0x0290;
		}
		*/
		//while(!TimerFlag);
		//TimerFlag = 0;
		
		//tick++;
		
		//if(tick == max_tick) tick = 0;
/*
		if(turn == 1)
		{
			rowData = 0x98;
			colData = 0x03C0;
		
			SR_RowWrite(rowData);
		
			SR_ColWrite(colData);
		}
		
		else if(turn == 2)
		{
			rowData = 0xEF;
			colData = 0x09C0;
		
			SR_RowWrite(rowData);
		
			SR_ColWrite(colData);
		}
		
		else if(turn == 3)
		{
			rowData = 0xF7;
			colData = 0x0390;
		
			SR_RowWrite(rowData);
		
			SR_ColWrite(colData);
		}
		
		else
		{
			rowData = 0x7F;
			colData = 0x09C0;
		
			SR_RowWrite(rowData);
		
			SR_ColWrite(colData);
		}
		
		
		while(!TimerFlag);
		TimerFlag = 0;
		turn += 1;
		
		if(turn == 4) turn = 0;*/
		/*
		if(turn == 1)
		{
			rowData = 0x18;
			colData = 0x03C0;
		
			SR_RowWrite(rowData);
		
			SR_ColWrite(colData);
		}
		
		else if(turn == 2)
		{
			rowData = 0xEF;
			colData = 0x09C0;
		
			SR_RowWrite(rowData);
		
			SR_ColWrite(colData);
		}
		
		else
		{
			rowData = 0xF7;
			colData = 0x0390;
		
			SR_RowWrite(rowData);
		
			SR_ColWrite(colData);
		}
		
		
		while(!TimerFlag);
		TimerFlag = 0;
		turn += 1;
		
		if(turn == 3) turn = 0;
		*/
		/*
		if(turn)
		{
			rowData = 0x10;
			colData = 0x03C0;
		
			SR_RowWrite(rowData);
		
			SR_ColWrite(colData);
		}
		
		else
		{
			rowData = 0xEF;
			colData = 0x09C0;
		
			SR_RowWrite(rowData);
		
			SR_ColWrite(colData);
		}
		
		while(!TimerFlag);
		TimerFlag = 0;
		turn = !turn;
		*/