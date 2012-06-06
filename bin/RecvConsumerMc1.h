#ifndef __RECVCONSUMERMC1_H__
#define __RECVCONSUMERMC1_H__

#include "general.h"
#include "DataStruct.h"

enum RecvConsumer_States { RC_Init_Wait, RC_dequeue };

int RecvConsumer_SMTick(int state) 
{
    const unsigned char mc = 1;
    const unsigned char func = RECV;
	
	static unsigned char c, i;
    
    /*State machine transitions*/
	switch (state) 
	{
		case RC_Init_Wait: /* Init */
			if (!empty_queue(mc, func)) 
			{
				state = RC_Init_Wait;
			}
			else
			{
				state = RC_dequeue;
				c = pop_queue(mc, func);
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

#endif //__RECVCONSUMERMC1_H__
