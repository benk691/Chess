#ifndef __SENDMC1_H__
#define __SENDMC1_H__

#include "general.h"
#include "QueueMc1.h"

enum SendProducer_States { SP_Init, SP_Gen };

int SendProducer_SMTick(int state) 
{	
	unsigned char msg = '?';
	
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
			push_s1queue(msg);
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
			if ( !s1queue_num_objs || !(UCSRA & (1 << UDRE)) )
            {
				state = SC_Init_Wait;
			}
			else
            {
				state = SC_dequeue_tx;
				UDR = pop_s1queue();
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

#endif //__SENDMC1_H__
