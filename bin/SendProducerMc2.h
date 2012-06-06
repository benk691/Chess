#ifndef __SENDPRODUCERMC2_H__
#define __SENDPRODUCERMC2_H__

#include "general.h"
#include "DataStruct.h"

enum SendProducer_States { SP_Init, SP_Gen };

unsigned char matrix[] =
{
	0x03,
	0x09,
	0xC0,
	0x0F
};

unsigned char size = 4;

int SendProducer_SMTick(int state) 
{
    const unsigned char mc = 2;
    const unsigned char func = SEND;

	static unsigned char i = 0;
	
	/*State machine transitions*/
	switch (state) 
	{
		case SP_Init: /* Init */
			state = SP_Gen;
			break;

		case SP_Gen:
			state = SP_Gen;
			break;

		default:
			state = SP_Init;
			break;
	}

	/*State machine actions*/
	switch(state) 
	{
		case SP_Init: /* Init */
			break;

		case SP_Gen:
			if(i >= size) { i = 0; }
			push_queue(mc, func, matrix[i]);
			i++;
			break;

		default:
			break;
	}
    
	return state;
}

/*Enumeration of states.*/
enum Consumer_States { C_Init_Wait, C_dequeue_tx };

int Consumer_SMTick(int state) {
	/*State machine transitions*/
	switch (state) 
	{
		case C_Init_Wait: /* Init */
			if ( !queue_num_objects || !(UCSRA & (1 << UDRE)) ) {
				state = C_Init_Wait;
			}
			else if (1) {
				state = C_dequeue_tx;
				UDR = pop_queue();
			}
			break;

		case C_dequeue_tx:
			if ( !(UCSRA & (1 << TXC)) ) {
				state = C_dequeue_tx;
			}
			else if (1) {
				state = C_Init_Wait;
			}
			break;

		default:
			state = C_Init_Wait;
			break;
	}

	/*State machine actions*/
	switch(state) 
	{
		case C_Init_Wait: /* Init */
			break;

		case C_dequeue_tx:
			break;

		default:
			break;
	}
	
	return state;
}

/*Add more state machines if necessary.*/


/*--------END User defined FSMs-----------------------------------------------*/


void init()
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	initUSART();
}

int main(void)
{
	init();
	
    //Period for LCD Interface task.(10 ms)
	//Period for Producer task. (50 ms)
	unsigned long int P_period_calc = 50;
	//Period for Consumer task.(1000 ms)
	unsigned long int C_period_calc = 100;

	//Calculating GCD
	unsigned long int tmpGCD = 1;
	tmpGCD = findGCD(P_period_calc, C_period_calc);

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int P_period = P_period_calc/GCD;
	unsigned long int C_period = C_period_calc/GCD;

	/*Declare an array of tasks and an integer containing the number of tasks in
	our system*/
	static task task1, task2; /*Add or delete tasks as necessary*/
	task *tasks[] = { &task1, &task2 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	//LCD interface
	//Producer
	task1.state = P_Init;//Task initial state.
	task1.period = P_period;//Task Period.
	task1.elapsedTime = P_period;//Task current elasped time.
	task1.TickFct = &Producer_SMTick;//Function pointer for the tick.

	//Consumer
	task2.state = C_Init_Wait;//Task initial state.
	task2.period = C_period;//Task Period.
	task2.elapsedTime = C_period;//Task current elasped time.
	task2.TickFct = &Consumer_SMTick;//Function pointer for the tick.

	//Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();

	unsigned short i; //Scheduler for-loop iterator
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
