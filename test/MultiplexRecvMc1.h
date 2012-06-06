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
	unsigned char k;
    
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
				if(c >= 'a' && c <= 'h')
				{
					switch(c)
					{
						case 'a':
							for(k = 0; k < matrix_size; k++)
							{
								if(k != 0)
								{
									col[k] = 0x0000;
								}
							}
							break;
						case 'b':
							for(k = 0; k < matrix_size; k++)
							{
								if(k != 1)
								{
									col[k] = 0x0000;
								}
							}
							break;
						case 'c':
							for(k = 0; k < matrix_size; k++)
							{
								if(k != 2)
								{
									col[k] = 0x0000;
								}
							}
							break;
						case 'd':
							for(k = 0; k < matrix_size; k++)
							{
								if(k != 3)
								{
									col[k] = 0x0000;
								}
							}
							break;
						case 'e':
							for(k = 0; k < matrix_size; k++)
							{
								if(k != 4)
								{
									col[k] = 0x0000;
								}
							}
							break;
						case 'f':
							for(k = 0; k < matrix_size; k++)
							{
								if(k != 5)
								{
									col[k] = 0x0000;
								}
							}
							break;
						case 'g':
							for(k = 0; k < matrix_size; k++)
							{
								if(k != 6)
								{
									col[k] = 0x0000;
								}
							}
							break;
						case 'h':
							for(k = 0; k < matrix_size; k++)
							{
								if(k != 7)
								{
									col[k] = 0x0000;
								}
							}
							break;
						default : break;
					}
					//SR_RowSend = 1;
				}
				else
				{
					switch(c)
					{
						case 1:
							col[c - 1] = 0x0001;
							break;
						case 2:
							col[c - 1] = 0x0002;
							break;
						case 3:
							col[c - 1] = 0x0004;
							break;
						case 4:
							col[c - 1] = 0x0008;
							break;
						case 5:
							col[c - 1] = 0x0010;
							break;
						case 6:
							col[c - 1] = 0x0020;
							break;
						case 7:
							col[c - 1] = 0x0040;
							break;
						case 8:
							col[c - 1] = 0x0080;
							break;
						default : break;
					}
					for(k = 0; k < matrix_size; k++)
					{
						if(k != (c - 1))
						{
							col[k] = 0x0000;
						}
					}
					//SR_ColSend = 1;
				}
				/*
				rowData = 0x00;
				colData = c;
				*/
				//SR_RowSend = 1;
				//SR_ColSend = 1;
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
