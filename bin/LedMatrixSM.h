#ifndef __LEDMATRIXSM_H__
#define __LEDMATRIXSM_H__

#include "ShiftReg.h"

enum LM_States { LM_Init, LM_Display } LM_State;

int LM_Tick(int state)
{
    static unsigned char k = 0;

    /*State machine transitions*/
	switch (state)
	{
        case -1:
            state = LM_Init;
            break;

		case LM_Init: /* Init */
		    state = LM_Display;
		    break;

		case LM_Display:
		    state = LM_Display;
		    break;

		default :   break;
	}

	/*State machine actions*/
	switch(state) 
	{
		case -1 : break;

		case LM_Init:
			for(unsigned char i = 0; i < matrix_size; i++)
            {
                col[i] = 0x03C0;
            }
			break;

        case LM_Display:
            if(k >= matrix_size)
            {
                k = 0;
            }

            rowData = row[k];
            colData = col[k];
            rowSend = 1;
            colSend = 1;
            k++;
            break;

		default:
			break;
	}
    
	return state;
}

#endif //__LEDMATRIXSM_H__
