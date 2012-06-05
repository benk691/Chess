/*
 * project.c
 *
 * Created: 6/4/2012 4:50:31 AM
 *  Author: Embedded Systems Lab
 */
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "ShiftReg.h"
#include "GameSM.h"

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

/*--------Find GCD function --------------------------------------------------*/
unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
    unsigned long int c;
    while(1)
	{
        c = a % b;
        if(c == 0){return b;}
        a = b;
        b = c;
    }
    return 0;
}
/*--------End find GCD function ----------------------------------------------*/

/*--------Bit-access functions -----------------------------------------------*/
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b)
{
    return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k)
{
    return ((x & (0x01 << k)) != 0);
}
/*--------END bit-access functions -------------------------------------------*/

/*--------Task scheduler data structure---------------------------------------*/
//Struct for Tasks represent a running process in our simple real-time operating system.
typedef struct _task {
    /*Tasks should have members that include: state, period,
        a measurement of elapsed time, and a function pointer.*/
    int state; //Task's current state
    unsigned long int period; //Task period
    unsigned long int elapsedTime; //Time elapsed since last task tick
    int (*TickFct)(int); //Task tick function
} task;

/*Declare an array of tasks and an integer containing the number of tasks in
our system*/
task task1, task2, task3; /*Add more tasks if necessary*/
task *tasks[] = { &task1, &task2, &task3 };
const int numTasks = sizeof(tasks)/sizeof(task*);

/*--------End Task scheduler data structure-----------------------------------*/
		
//Implement scheduler code from PES.
int main()
{
    SRInit();

    //Period for Game
	unsigned long int Game_period_calc = 500;
	unsigned long int SR_Row_period_calc = 1;
	unsigned long int SR_Col_period_calc = 1;
	
    //Calculating GCD
    unsigned long int GCD = 1;
    GCD = findGCD(Game_period_calc, SR_Row_period_calc);
	GCD = findGCD(GCD, SR_Col_period_calc);

    //Recalculate GCD periods for scheduler
	unsigned long int Game_period = Game_period_calc/GCD;
	unsigned long int SR_Row_period = SR_Row_period_calc/GCD;
	unsigned long int SR_Col_period = SR_Col_period_calc/GCD;

    //SR Row
    task1.state = -1;//Task initial state.
    task1.period = SR_Row_period;//Task Period.
    task1.elapsedTime = SR_Row_period;//Task current elasped time.
    task1.TickFct = &SR_RowTick;//Function pointer for the tick.
	
	//SR Col
    task2.state = -1;//Task initial state.
    task2.period = SR_Col_period;//Task Period.
    task2.elapsedTime = SR_Col_period;//Task current elasped time.
    task2.TickFct = &SR_ColTick;//Function pointer for the tick.
	
	//Game
	task3.state = -1;//Task initial state.
    task3.period = Game_period;//Task Period.
    task3.elapsedTime = Game_period;//Task current elasped time.
    task3.TickFct = &Game_Tick;//Function pointer for the tick.

    //Set the timer and turn it on
    TimerSet(GCD);
    TimerOn();
	
    unsigned int i; //Scheduler for-loop iterator
    while(1) 
	{
        //Scheduler code
        for ( i = 0; i < numTasks; i++ ) 
		{
            //Task is ready to tick
            if ( tasks[i]->elapsedTime == tasks[i]->period ) 
			{
                //Setting next state for task
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                //Reset the elapsed time for next tick.
                tasks[i]->elapsedTime = 0;
            }
            tasks[i]->elapsedTime += 1;
        }
        while(!TimerFlag);
        TimerFlag = 0;
    }
    /*Error: Program should not exit!*/
    return 0;
}
