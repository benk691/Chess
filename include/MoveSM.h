#ifndef __MOVESM_H__
#define __MOVESM_H__

#include "general.h"

enum Move_States { Move_Wait, Move_SetRow, Move_SetCol, Move_Clear,
Move_Piece, Move_Select } Move_State;

typedef struct
{
    unsigned char col;
    unsigned char row;

    unsigned char cSet;
    unsigned char rSet;
} Move;

void selection(Move m);

int Move_Tick(int state)
{
    static Move move;
    static Move piece;
    static unsigned char select = 0;

    unsigned char r;

    //Transitions
    switch(state)
    {
        case -1 :
            turn = WHITE;
            Move_RowSend = 0;
            Move_ColSend = 0;
            move.col = 0;
            move.row = 0;
            move.cSet = 0;
            move.rSet = 0;
            piece.col = 0;
            piece.row = 0;
            piece.cSet = 0;
            piece.rSet = 0;
            select = 1;
            state = Move_Wait;
            break;

        case Move_Wait:
            if(!select)
            {
                if(move.rSet && move.cSet)
                {
                    state = Move_Piece;
                }
                else if(!move.rSet && Move_RowSend)
                {
                    state = Move_SetRow;
                }
                else if(!move.cSet && Move_ColSend)
                {
                    state = Move_SetCol;
                }
                else
                {
                    state = Move_Wait;
                }
            }
            else
            {
                if(piece.rSet && piece.cSet)
                {
                    state = Move_Select;
                }
                else if(!piece.rSet && Move_RowSend)
                {
                    state = Move_SetRow;
                }
                else if(!piece.cSet && Move_ColSend)
                {
                    state = Move_SetCol;
                }
                else
                {
                    state = Move_Wait;
                }
            }
            break;

        case Move_SetRow:
Move_RowSend = 0;
            if(!select)
            {
                move.rSet = 1;
            }
            else
            {
                piece.rSet = 1;
            }
            state = Move_Wait;
            break;

        case Move_SetCol:
Move_ColSend = 0;
            if(!select)
            {
                move.cSet = 1;
            }
            else
            {
                piece.cSet = 1;
            }
            state = Move_Wait;
            break;

        case Move_Piece:
            state = Move_Clear;
            break;

        case Move_Select:
            state = Move_Clear;
            break;

        case Move_Clear:
            state = Move_Wait;
            break;

        default:break;
    }

    //Actions
    switch(state)
    {
        case -1 : break;

        case Move_Wait : break;

        case Move_SetRow:
if(!select)
            {
                move.row = Move_Row;
            }
            else
            {
                piece.row = Move_Row;
            }
            break;

        case Move_SetCol:
if(!select)
            {
                move.col = Move_Col;
            }
            else
            {
                piece.col = Move_Col;
            }
            break;

        case Move_Piece:
move.row = (move.row - (int)('a'));
//select = !select;
            break;

        case Move_Select:
            piece.row = (piece.row - (int)('a'));
selection(piece);
//select = !select;
            break;

        case Move_Clear:
            move.rSet = 0;
            move.cSet = 0;
            piece.rSet = 0;
            piece.cSet = 0;
            break;
    }

    return state;
}

void selection(Move m)
{
    switch(turn)
    {
        case WHITE:
            if(m.col == 2)
            {
                col[ m.row ] = (col[ m.col - 1 ] | (0x00FE & (col[ m.col - 1 ] >> 8)));
            }
            else if(m.col == 1)
            {
                col[ m.row ] = (col[ m.col - 1 ] | (0x00FD & (col[ m.col - 1 ] >> 8)));
            }
            else
            {
                col[ m.row ] = 0xABCD;
            }
            break;

        case BLACK:
            col[ m.row ] &= 0xFF00;
                    break;

        default:
            break;
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
}

#endif //__MOVESM_H__
