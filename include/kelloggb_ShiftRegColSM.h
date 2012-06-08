/*
 * kelloggb_ShiftRegColSM.h - 06/08/2012
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
#ifndef __SHIFTREGCOLSM_H__
#define __SHIFTREGCOLSM_H__

#include "general.h"
#include "PinMap.h"

enum SR_ColStates { SR_ColInit, SR_ColWait, SR_ColWrite } SR_ColState;

int SR_ColTick(int state)
{
    static unsigned long oldData = 0x0000;
    static unsigned long data = 0x0000;

    // Transitions
    switch(state)
    {
        case -1     :   state = SR_ColInit;
                        break;

        case SR_ColInit :   state = SR_ColWait;
                            break;

        case SR_ColWait :   if(!SR_ColSend)
                            {
                                state = SR_ColWait;
                            }
                            else if(colData != oldData)
                            {
                                oldData = colData;
                                data = colData;
                                state = SR_ColWrite;
                            }
                            break;
        
        case SR_ColWrite    :  state = SR_ColWait;
                               break;
							   
        default             :   break;
    }

    // State Actions
    switch(state)
    {
        case -1     :   break;

        case SR_ColInit :   SR_ColSend = 0;
                            break;

        case SR_ColWait :   break;
        
        case SR_ColWrite    :   for(unsigned char i = 0; i < 16; i++)
                                {
                                    // Output the data on DS line according to the
                                    // Value of MSB
                                    if(data & 0x8000)
                                    {
                                        // MSB is 1 so output high
                                        SR_COL_PORT |= (1 << SR_COL_SER); // High
                                    }
                                    else
                                    {
                                        // MSB is 0 so output low
                                        SR_COL_PORT &= (~(1 << SR_COL_SER)); // Low
                                    }

                                    //Pulse the Clock line
                                    SR_COL_PORT |= (1 << SR_COL_SRCLK); //High

                                    SR_COL_PORT &= (~(1 << SR_COL_SRCLK)); // Low

                                    data = data << 1;  //Now bring next bit at MSB position
                                }
								
								SR_COL_PORT |= (1 << SR_COL_RCLK); // High
								asm("nop");
								
								SR_COL_PORT &= (~(1 << SR_COL_RCLK)); // Low
								asm("nop");
								
								SR_ColSend = 0;
                                break;
								
        default             :   break;
    }
    
    return state;
}

#endif //__SHIFTREGCOLSM_H__
