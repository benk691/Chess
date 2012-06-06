#ifndef __SENDCONSUMERMC2_H__
#define __SENDCONSUMERMC2_H__

#include "general.h"
#include "DataStruct.h"

enum SendConsumer_States { SC_Init_Wait, SC_dequeue_tx };

int SendConsumer_SMTick(int state)
{
	/*State machine transitions*/
	switch (state) 
	{
		case SC_Init_Wait: /* Init */
			if ( !empty_queue(SEND) || !(UCSRA & (1 << UDRE)) )
            {
				state = SC_Init_Wait;
			}
			else
            {
				state = SC_dequeue_tx;
				UDR = pop_queue(SEND);
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

#endif //__SENDCONSUMERMC2_H__
