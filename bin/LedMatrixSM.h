#ifndef __LEDMATRIXSM_H__
#define __LEDMATRIXSM_H__

#include "ShiftReg.h"

// Performs Time Multiplexing

enum LM_States { LM_Init, LM_Display, LM_Unique } LM_State;
	
void initRow()
{
	row[0] = 0xFE;  //1111 1110
	row[1] = 0xFD;  //1111 1101
	row[2] = 0xFB;  //1111 1011
	row[3] = 0xF7;  //1111 0111
	row[4] = 0xEF;  //1110 1111
	row[5] = 0xDF;  //1101 1111
	row[6] = 0xBF;  //1011 1111
	row[7] = 0x7F;  //0111 1111
	row[8] = 0xFF;  //1111 1111
}

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
			if(LM_enable_unique)
			{
				state = LM_Unique;
			}
			else
			{
				k = 0;
				state = LM_Display;
			}
		    break;

		case LM_Display:
			if(LM_enable_unique)
			{
				state = LM_Unique;
			}
			else
			{
				state = LM_Display;
			}
		    break;
			
		case LM_Unique:
			if(LM_enable_unique)
			{
				state = LM_Unique;
			}
			else
			{
				k = 0;
				state = LM_Display;
			}
		    break;

		default :   break;
	}

	/*State machine actions*/
	switch(state) 
	{
		case -1 : break;

		case LM_Init:
			initRow();
			for(unsigned char i = 0; i < matrix_size; i++)
            {
                col[i] = 0x03C0; //GG BB BB RR
            }
			break;

        case LM_Display:
			if(k >= matrix_size)
			{
				k = 0;
			}
			
			rowData = row[k];
			SR_RowSend = 1;
			
			colData = col[k];
			SR_ColSend = 1;
			
			k++;
            break;
			
		case LM_Unique:
			rowData = row[LM_unique_row];
			colData = col[LM_unique_col];
			SR_RowSend = 1;
			SR_ColSend = 1;
			break;

		default:
			break;
	}
    
	return state;
}

#endif //__LEDMATRIXSM_H__
