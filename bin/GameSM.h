#ifndef __GAMESM_H__
#define __GAMESM_H__

#include "general.h"

enum Game_States { Game_Init, Game_WMove, Game_BMove, Game_Wait_SR_Rdy } Game_State;

int Game_Tick(int state)
{	
    static int preWaitState = -1;

	// Transitions
	switch(state)
	{
		case -1				:	if(!SR_ColRdy || !SR_RowRdy)
                                {
                                    preWaitState = Game_Init;
                                    state = Game_Wait_SR_Rdy;
                                }
                                else
                                {
                                    state = Game_Init;
                                }
								break;
		
		case Game_Init		:	if(!SR_ColRdy || !SR_RowRdy)
                                {
                                    preWaitState = Game_WMove;
                                    state = Game_Wait_SR_Rdy;
                                }
                                else
                                {
                                    state = Game_WMove;
                                }
								break;
		
		case Game_WMove		:	if(!SR_ColRdy || !SR_RowRdy)
                                {
                                    preWaitState = Game_BMove;
                                    state = Game_Wait_SR_Rdy;
                                }
                                else
                                {
                                    state = Game_BMove;
                                }
								break;
		
		case Game_BMove		:	if(!SR_ColRdy || !SR_RowRdy)
                                {
                                    preWaitState = Game_Init;
                                    state = Game_Wait_SR_Rdy;
                                }
                                else
                                {
                                    state = Game_Init;
                                }
								break;

        case Game_Wait_SR_Rdy   :   if(!SR_ColRdy || !SR_RowRdy)
                                    {
                                        state = Game_Wait_SR_Rdy;
                                    }
                                    else
                                    {
                                        state = preWaitState;
                                    }
                                    break;
		
		default				:	break;
	}
	
	// State Actions
	switch(state)
	{
		case -1				:	break;
		
		case Game_Init		:	rowData = 0x00;
								colData = 0x03C0;
                                SR_RowSend = 1;
                                SR_ColSend = 1;
								break;
		
		case Game_WMove		:	rowData = 0x00;
								colData = 0x09C0;
                                SR_RowSend = 1;
                                SR_ColSend = 1;
								break;
		
		case Game_BMove		:	rowData = 0xEF;
								colData = 0x0990;
                                SR_RowSend = 1;
                                SR_ColSend = 1;
								break;

        case Game_Wait_SR_Rdy   :   break;
		
		default				:	break;
	}
	
	return state;
}

#endif //__GAMESM_H__
