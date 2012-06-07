#ifndef __RECVMC2_H__
#define __RECVMC2_H__

#include "general.h"
#include "QueueMc2.h"

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
			push_r2queue(UDR);
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
	static unsigned char c;
	static unsigned char i = 0;
    
    /*State machine transitions*/
	switch (state) 
	{
		case RC_Init_Wait: /* Init */
			if (!r2queue_num_objs) 
			{
				state = RC_Init_Wait;
			}
			else
			{
				state = RC_dequeue;
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
			LCD_go_g = 0;
			break;

		case RC_dequeue:
			c = pop_r2queue();
			
			if(c != '\0')
			{
				for(i = 0; i < 16; i++)
				{
					LCD_string_g[i] = c;
				}
				LCD_string_g[i] = '\0';
				LCD_go_g = 1;	
			}
			break;

		default:
			break;
	}

	return state;
}

#endif //__RECVMC2_H__
