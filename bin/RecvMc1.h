#ifndef __RECVMC1_H__
#define __RECVMC1_H__

#include "general.h"
#include "Queue.h"

enum RecvProducer_States { RP_Init_Wait, RP_enqueue_rx };

int RecvProducer_SMTick(int state)
{
	static unsigned char dummy;
    
    /*State machine transitions*/
	switch (state)
	{
		case RP_Init_Wait: /* Init */
		if ( !(UCSRA & (1 << RXC)) ) 
		{
			state = RP_Init_Wait;
		}
		else
		{
			state = RP_enqueue_rx;
			push_rqueue(UDR);
		}
		break;

		case RP_enqueue_rx:
		if ( UCSRA & (1 << RXC) )
		{
			state = RP_enqueue_rx; // flush buffer
		}
		else if (1) 
		{
			state = RP_Init_Wait;
		}
		break;

		default:
		state = RP_Init_Wait;
		break;
	}

	/*State machine actions*/
	switch(state) 
	{
		case RP_Init_Wait: /* Init */
			break;

		case RP_enqueue_rx:
			dummy = UDR;
			break;

		default:
			break;
	}
    
	return state;
}

enum RecvConsumer_States { RC_Init_Wait, RC_dequeue };

int RecvConsumer_SMTick(int state) 
{
	static unsigned char c, i;
    
    /*State machine transitions*/
	switch (state) 
	{
		case RC_Init_Wait: /* Init */
			if (!rqueue_num_objs) 
			{
				state = RC_Init_Wait;
			}
			else
			{
				state = RC_dequeue;
				c = pop_rqueue();
				rowData = 0x00;
				colData = c;
				SR_RowSend = 1;
				SR_ColSend = 1;
			}
			break;

		case RC_dequeue:
			state = RC_Init_Wait;
			break;

		default:
			state = RC_Init_Wait;
			break;
	}

    /*State machine actions*/
	switch(state) 
	{
		case RC_Init_Wait: /* Init */
			break;

		case RC_dequeue:
			break;

		default:
			break;
	}

	return state;
}

#endif //__RECVMC1_H__
