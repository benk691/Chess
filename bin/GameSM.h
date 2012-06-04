#ifndef __GAMESM_H__
#define __GAMESM_H__

#include "ShiftReg.h"

enum Game_States { Game_WaitInit, Game_Init, Game_WMove, Game_BMove } Game_State;

int Game_Tick(int state)
{	
	// Transitions
	switch(state)
	{
		case -1				:	state = Game_WaitInit;
								break;
		
		case Game_WaitInit	:	state = LM_rdy ? Game_Init : Game_WaitInit;
								break;
		
		case Game_Init		:	state = Game_WMove;
								break;
		
		case Game_WMove		:	state = Game_BMove;
								break;
		
		case Game_BMove		:	state = Game_Init;
								break;
		
		default				:	break;
	}
	
	// State Actions
	switch(state)
	{
		case -1				:	break;
		
		case Game_WaitInit	:	break;
		
		case Game_Init		:	rowData = 0x00;
								colData = 0x03C0;
								SR_RowWrite(rowData);
								SR_ColWrite(colData);
								break;
		
		case Game_WMove		:	rowData = 0x00;
								colData = 0x09C0;
								SR_RowWrite(rowData);
								SR_ColWrite(colData);
								break;
		
		case Game_BMove		:	rowData = 0xEF;
								colData = 0x0990;
								SR_RowWrite(rowData);
								SR_ColWrite(colData);
								break;
		
		default				:	break;
	}
	
	return state;
}

#endif //__GAMESM_H__