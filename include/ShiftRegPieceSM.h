#ifndef __SHIFTREGPIECESM_H__
#define __SHIFTREGPIECESM_H__

#include "general.h"
#include "PinMap.h"

enum SR_PieceStates { SR_PieceInit, SR_PieceWait, SR_PieceWrite } SR_PieceState;

int SR_PieceTick(int state)
{
    static unsigned long oldData = 0x0000;
    static unsigned long data = 0x0000;

    // Transitions
    switch(state)
    {
        case -1     :   state = SR_PieceInit;
                        break;
        
        case SR_PieceInit : state = SR_PieceWait;
                            break;

        case SR_PieceWait : if(!SR_PieceSend)
                            {
                                state = SR_PieceWait;
                            }
                            else if(pieceData != oldData)
                            {
                                oldData = pieceData;
                                data = pieceData;
                                state = SR_PieceWrite;
                            }
                            break;
        
        case SR_PieceWrite    :  state = SR_PieceWait;
                                 break;

        default             :   break;
    }

    // State Actions
    switch(state)
    {
        case -1     :   break;

        case SR_PieceInit :   SR_PieceSend = 0;
                              break;

        case SR_PieceWait :   break;
        
        case SR_PieceWrite    :  for(unsigned char i = 0; i < 16; i++)
                                {
                                    // Output the data on DS line according to the
                                    // Value of MSB
                                    if(data & 0x8000)
                                    {
                                        // MSB is 1 so output high
                                        SR_PIECE_PORT |= (1 << SR_PIECE_SER); // High
                                    }
                                    else
                                    {
                                        // MSB is 0 so output low
                                        SR_PIECE_PORT &= (~(1 << SR_PIECE_SER)); // Low
                                    }

                                    //Pulse the Clock line
                                    SR_PIECE_PORT |= (1 << SR_PIECE_SRCLK); //High

                                    SR_PIECE_PORT &= (~(1 << SR_PIECE_SRCLK)); // Low

                                    data = data << 1;  //Now bring next bit at MSB position
                                }
								
								SR_PIECE_PORT |= (1 << SR_PIECE_RCLK); // High
								asm("nop");
								
								SR_PIECE_PORT &= (~(1 << SR_PIECE_RCLK)); // Low
								asm("nop");
								
								SR_PieceSend = 0;
                                break;

        default             :   break;
    }
    
    return state;
}

#endif //__SHIFTREGPIECESM_H__
