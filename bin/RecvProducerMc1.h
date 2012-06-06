#ifndef __RECVPRODUCERMC1_H__
#define __RECVPRODUCERMC1_H__

#include "general.h"
#include "DataStruct.h"

enum RecvProducer_States { RP_Init_Wait, RP_enqueue_rx };

int RecvProducer_SMTick(int state)
{
    const unsigned char mc = 1;
    const unsigned char func = RECV;
	
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
			push_queue(mc, func, UDR);
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

#endif //__RECVPRODUCERMC1_H__
