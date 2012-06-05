#ifndef __SHIFTREGCOLSM_H__
#define __SHIFTREGCOLSM_H__

#include "general.h"
#include "PinMap.h"

enum SR_ColStates { SR_ColInit, SR_ColWait, SR_ColWrite, SR_ColLatchHigh, SR_ColLatchLow } SR_ColState;

int SR_ColTick(int state)
{
    static unsigned long oldData = 0x0000;
    static unsigned long data = 0x0000;

    // Transitions
    switch(state)
    {
        case -1     :   SR_ColRdy = 0;
                        state = SR_ColInit;
                        break;

        case SR_ColInit :   state = SR_ColWait;
                            break;

        case SR_ColWait :   if(!SR_ColSend)
                            {
                                state = SR_ColWait;
                            }
                            else if(colData != oldData)
                            {
                                SR_ColRdy = 0;
                                oldData = colData;
                                data = colData;
                                state = SR_ColWrite;
                            }
                            break;
        
        case SR_ColWrite    :  state = SR_ColLatchHigh;
                               break;

        case SR_ColLatchHigh    :   state = SR_ColLatchLow;
                                    break;

        case SR_ColLatchLow    :   SR_ColSend = 0;
                                   SR_ColRdy = 1;
                                   state = SR_ColWait;
                                   break;

        default             :   break;
    }

    // State Actions
    switch(state)
    {
        case -1     :   break;

        case SR_ColInit :   SR_ColSend = 0;
                            SR_ColRdy = 1;
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
                                break;

        case SR_ColLatchHigh    :   SR_COL_PORT |= (1 << SR_COL_RCLK); // High
                                    break;

        case SR_ColLatchLow    :   SR_COL_PORT &= (~(1 << SR_COL_RCLK)); // Low
                                   break;

        default             :   break;
    }
    
    return state;
}

#endif //__SHIFTREGCOLSM_H__
