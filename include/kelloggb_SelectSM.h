/*
 * kelloggb_SelectSM.h - 06/08/2012
 * Name & E-mail: Benjamin Kellogg kelloggb@cs.ucr.edu
 * CS Login: kelloggb
 * Partner(s) Name & E-mail: Gabriel Limon glimo002@ucr.edu
 * Lab Section: 021
 * Assignment: Lab Project
 * Project Description: This game is based off of chess, but is more like guessing 
 * 	which locations have positive or negative points.
 * 
 * I acknowledge all content contained herein is my own original work.
 */
#ifndef __SELECTSM_H__
#define __SELECTSM_H__

#include "general.h"

enum Select_States { Select_Wait, Select_SetRow, Select_SetCol, Select_Piece, Select_Clear } Select_State;

typedef struct
{
    unsigned char col;
    unsigned char row;

    unsigned char cSet;
    unsigned char rSet;
} Select;

void selection(Select m);

int Select_Tick(int state)
{
    static Select s;

    //Transitions
    switch(state)
    {
        case -1 :
			turn = WHITE;
			Select_RowSend = 0;
			Select_ColSend = 0;
            s.col = 0;
            s.row = 0;
            s.cSet = 0;
            s.rSet = 0;
            state = Select_Wait;
            break;

        case Select_Wait:
			sound_on = 0;
            if(s.rSet && s.cSet)
            {
                state = Select_Piece;
            }
            else if(!s.rSet && Select_RowSend)
            {
                state = Select_SetRow;
            }
            else if(!s.cSet && Select_ColSend)
            {
                state = Select_SetCol;
            }
            else
            {
                state = Select_Wait;
            }
            break;

        case Select_SetRow:
			Select_RowSend = 0;
            s.rSet = 1;
            state = Select_Wait;
            break;

        case Select_SetCol:
			Select_ColSend = 0;
            s.cSet = 1;
            state = Select_Wait;
            break;

        case Select_Piece:
            state = Select_Clear;
            break;
			
		case Select_Clear:
            state = Select_Wait;
            break;

        default:break;
    }

    //Actions
    switch(state)
    {
        case -1 :    break;

        case Select_Wait  :   break;

        case Select_SetRow:
			s.row = Select_Row;
            break;

        case Select_SetCol:
			s.col = Select_Col;
            break;

        case Select_Piece:
			s.row =  (s.row - (int)('a'));
            selection(s);
            break;
			
		case Select_Clear:
            s.cSet = 0;
            s.rSet = 0;
            break;
    }

    return state;
}

void selection(Select m)
{
    unsigned long dval = 0x03C0;

	for(unsigned char j = 0; j < matrix_size; j++)
	{
		col[j] = dval;
	}
	
    if(GetBit(col[m.row], m.col - 1) == 0 && GetBit(col[m.col - 1], m.row) == 0)
    {
        switch(turn)
        {
            case WHITE:
                if(whiteScore < 9)
                {
                    whiteScore += 1;
					sound_on = 1;
                }
                break;

            case BLACK:
                if(blackScore < 9)
                {
                    blackScore += 1;
					sound_on = 1;
                }
                break;
        }
    }
    else
    {
        switch(turn)
        {
            case WHITE:
                if(whiteScore > 0)
                {
                    whiteScore -= 1;
					sound_on = 0;
                }
                break;

            case BLACK:
                if(blackScore > 0)
                {
                    blackScore -= 1;
					sound_on = 0;
                }
                break;
        }
    }
switch(turn)
{
	case WHITE:
		switch(m.col)
		{
			case 1:
				col[m.row] |= 0x0001;
				break;
			case 2:
				col[m.row] |= 0x0002;
				break;
			case 3:
				col[m.row] |= 0x0004;
				break;
			case 4:
				col[m.row] |= 0x0008;
				break;
			case 5:
				col[m.row] |= 0x0010;
				break;
			case 6:
				col[m.row] |= 0x0020;
				break;
			case 7:
				col[m.row] |= 0x0040;
				break;
			case 8:
				col[m.row] |= 0x0080;
				break;
			default : break;
		}
		break;
	
	case BLACK:
		switch(m.col)
		{
			case 1:
				col[m.row] |= 0x0100;
				break;
			case 2:
				col[m.row] |= 0x0200;
				break;
			case 3:
				col[m.row] |= 0x0400;
				break;
			case 4:
				col[m.row] |= 0x0800;
				break;
			case 5:
				col[m.row] |= 0x1000;
				break;
			case 6:
				col[m.row] |= 0x2000;
				break;
			case 7:
				col[m.row] |= 0x4000;
				break;
			case 8:
				col[m.row] |= 0x8000;
				break;
			default : break;
		}
		
	default: break;
}	
	
	if(m.col == 2)
	{
		piece = PAWN;
	}
	else
	{
		switch(m.row)
		{
			case 0:
			case 7:
				piece = ROOK;
				break;
				
			case 1:
			case 6:
				piece = KNIGHT;
				break;
				
			case 2:
			case 5:
				piece = BISHOP;
				break;
				
			case 3:
				piece = QUEEN;
				break;
			
			case 4:
				piece = KING;
				break;
				
			default:
				piece = NONE;
				break;
		}
	}

    turn = !turn;
}

#endif //__SELECTSM_H__
