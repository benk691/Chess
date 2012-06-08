#ifndef __PIECEDISPLAYSM_H__
#define __PIECEDISPLAYSM_H__

#include "ShiftRegPieceSM.h"

enum PieceDisplayStates { Piece_Init, Piece_Display } PieceDisplayState;

void pieceDisplay();

int PieceDisplay_Tick(int state)
{
    static unsigned long oldData = 0;

    // Transitions
    switch(state)
    {
        case -1:
            state = Piece_Init;
            break;

        case Piece_Init:
            state = Piece_Display;
            break;

        case Piece_Display:
            state = Piece_Display;
            break;

        default :   break;
            
    }

    //Actions
    switch(state)
    {
        case Piece_Init:
            pieceData = 0xFFFF;
			oldData = pieceData;
            SR_PieceSend = 1;
            break;

        case Piece_Display:
			pieceDisplay();
			if(pieceData != oldData)
			{
				oldData = pieceData;
				SR_PieceSend = 1;
			}			
            break;

        default :   break;
            
    }

    return state;
}

void pieceDisplay()
{
    switch(piece)
    {
		case NONE : 
            pieceData = 0xFFFF; //1111 1111 1111 1111
            break;
			
        case PAWN : 
            pieceData = 0xE3E2; //1110 0011 1110 0010
            break;
			
		case KNIGHT : 
            pieceData = 0x97E9; //1001 0111 1110 1001
            break;
			
		case BISHOP : 
            pieceData = //0x39C2; //0011 1001 1100 0010
						//0xFE42; //1111 1110 0100 0010
						0x43C2; //0100 0011 1100 0010
            break;
			
		case ROOK : 
            pieceData = 0xA3E2; //1010 0011 1110 0010
            break;
			
		case QUEEN : 
            pieceData = 0x13CA; //0001 0011 1100 1010
            break;
			
		case KING : 
            pieceData = 0xBDE3; //1011 1101 1110 0011
            break;

        default:    break;
    }
}

#endif //__PIECEDISPLAYSM_H__
