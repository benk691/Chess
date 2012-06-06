#ifndef __SENDMC2_H__
#define __SENDMC2_H__

#include "general.h"
#include "Queue.h"

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
				push_squeue(key);
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
			if ( !squeue_num_objs || !(UCSRA & (1 << UDRE)) )
            {
				state = SC_Init_Wait;
			}
			else
            {
				state = SC_dequeue_tx;
				UDR = pop_squeue();
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
