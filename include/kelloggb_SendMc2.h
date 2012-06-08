/*
 * kelloggb_SendMc2.h - 06/08/2012
 * Name & E-mail: Benjamin Kellogg kelloggb@cs.ucr.edu
 * CS Login: kelloggb
 * Partner(s) Name & E-mail: Gabriel Limon glimo002@ucr.edu
 * Lab Section: 021
 * Assignment: Lab Project
 * Project Description: This game is based off of chess, but is more like guessing 
 * 	which locations have positive or negative points.
 * 
 * I acknowledge all content contained herein is my own original work.
 */
#ifndef __SENDMC2_H__
#define __SENDMC2_H__

#include "general.h"
#include "QueueMc2.h"

enum SendProducer_States { SP_Init, SP_Gen };

int SendProducer_SMTick(int state) 
{	
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
			if(key != '\0')
			{
				sound_on = 1;
				push_s2queue(key);
			}
			else
			{
				sound_on = 0;
			}
			break;

		default:
			break;
	}
    
	return state;
}

enum SendConsumer_States { SC_Init_Wait, SC_dequeue_tx };

int SendConsumer_SMTick(int state)
{
	
	/*State machine transitions*/
	switch (state) 
	{
		case SC_Init_Wait: /* Init */
			if ( !s2queue_num_objs || !(UCSRA & (1 << UDRE)) )
            {
				state = SC_Init_Wait;
			}
			else
            {
				state = SC_dequeue_tx;
				UDR = pop_s2queue();
			}
			break;

		case SC_dequeue_tx:
			if ( !(UCSRA & (1 << TXC)) )
            {
				state = SC_dequeue_tx;
			}
			else
            {
				state = SC_Init_Wait;
			}
			break;

		default:
			state = SC_Init_Wait;
			break;
	}

	/*State machine actions*/
	switch(state) 
	{
		case SC_Init_Wait: /* Init */
			break;

		case SC_dequeue_tx:
			break;

		default:
			break;
	}
	
	return state;
}

#endif //__SENDMC2_H__
