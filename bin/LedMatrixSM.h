#ifndef __LEDMATRIXSM_H__
#define __LEDMATRIXSM_H__

#include "ShiftReg.h"

enum LM_States { LM_Init, LM_Game } LM_State;

int LM_Tick(int state)
{	
	// Transitions
	switch(state)
	{
		case -1			:	LM_rdy = 0;
							rowData = 0x00;
							colData = 0x0000;
							state = LM_Init;
							break;
		
		case LM_Init	:	LM_rdy = 1;
							state = LM_Game;
							break;
		
		case LM_Game	:	if(!reset)
							{
								state = LM_Game;
							}
							else
							{
								LM_rdy = 0;
								rowData = 0x00;
								colData = 0x0000;
								state = LM_Init;
							}
							break;
		
		default			:	break;
	}
	
	// State Actions
	switch(state)
	{
		case -1			:	break;
		
		case LM_Init	:	SR_RowWrite(rowData);
							SR_ColWrite(colData);
							break;
		
		case LM_Game	:	break;
		
		default			:	break;
	}
	
	return state;
}

#endif //__LEDMATRIXSM_H__