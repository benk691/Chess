#ifndef __SHIFTREGROWSM_H__
#define __SHIFTREGROWSM_H__

#include "general.h"
#include "PinMap.h"

enum SR_RowStates { SR_RowInit, SR_RowWait, SR_RowWrite } SR_RowState;

int SR_RowTick(int state)
{
    static unsigned char oldData = 0x00;
    static unsigned char data = 0x00;

    // Transitions
    switch(state)
    {
        case -1     :   state = SR_RowInit;
                        break;
        
        case SR_RowInit :   state = SR_RowWait;
                            break;

        case SR_RowWait :   if(!SR_RowSend)
                            {
                                state = SR_RowWait;
                            }
                            else if(rowData != oldData)
                            {
                                oldData = rowData;
                                data = rowData;
                                state = SR_RowWrite;
                            }
                            break;
        
        case SR_RowWrite    :  state = SR_RowWait;
                               break;

        default             :   break;
    }

    // State Actions
    switch(state)
    {
        case -1     :   break;

        case SR_RowInit :   SR_RowSend = 0;
                            break;

        case SR_RowWait :   break;
        
        case SR_RowWrite    :   for(unsigned char i = 0; i < 8; i++)
                                {
                                    // Output the data on DS line according to the
                                    // Value of MSB
                                    if(data & 0x80)
                                    {
                                        // MSB is 1 so output high
                                        SR_ROW_PORT |= (1 << SR_ROW_SER); // High
                                    }
                                    else
                                    {
                                        // MSB is 0 so output low
                                        SR_ROW_PORT &= (~(1 << SR_ROW_SER)); // Low
                                    }

                                    //Pulse the Clock line
                                    SR_ROW_PORT |= (1 << SR_ROW_SRCLK); //High

                                    SR_ROW_PORT &= (~(1 << SR_ROW_SRCLK)); // Low

                                    data = data << 1;  //Now bring next bit at MSB position
                                }
								
								SR_ROW_PORT |= (1 << SR_ROW_RCLK); // High
								asm("nop");
								
								SR_ROW_PORT &= (~(1 << SR_ROW_RCLK)); // Low
								asm("nop");
								
								SR_RowSend = 0;
                                break;

        default             :   break;
    }
    
    return state;
}

#endif //__SHIFTREGROWSM_H__
