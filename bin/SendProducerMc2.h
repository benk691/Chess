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
			push_queue(SEND, matrix[i]);
			i++;
			break;

		default:
			break;
	}
    
	return state;
}

#endif //__SENDPRODUCERMC2_H__
