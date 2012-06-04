#ifndef __SHIFTREGROWSM_H__
#define __SHIFTREGROWSM_H__

#include <util/delay.h>
#include "general.h"
#include "PinMap.h"

enum SR_RowStates { SR_RowWait, SR_RowWrite, SR_RowLatchHigh, SR_RowLatchLow } SR_RowState;

void SR_RowSerHigh()
{
	SR_ROW_PORT |= (1 << SR_ROW_SER);
}	

void SR_RowSerLow()
{
	SR_ROW_PORT &= (~(1 << SR_ROW_SER));
}

int SR_Tick(int state)
{
    static unsigned char data = 0x00;

    // Transitions
    switch(state)
    {
        case -1     :   state = SR_RowWait;
                        break;

        case SR_RowWait :   if(!SR_RowSend)
                            {
                                state = SR_RowWait;
                            }
                            else
                            {
                                data = rowData;
                                state = SR_RowWrite;
                            }
                            break;
        
        case SR_RowWrite    :  state = SR_RowLatchHigh;
                               break;

        case SR_RowLatchHigh    :   state = SR_RowLatchLow;
                                    break;

        case SR_RowLatchLow    :   state = SR_RowWait;
                                   break;

        default             :   break;
    }

    // State Actions
    switch(state)
    {
        case -1     :   break;

        case SR_RowWait :   break;
        
        case SR_RowWrite    :  for(unsigned char i = 0; i < 8; i++)
                               {
                                  //Output the data on DS line according to the
                                  //Value of MSB
                                  if(data & 0x80)
                                  {
                                     //MSB is 1 so output high
                                     SR_RowSerHigh();
                                  }
                                  else
                                  {
                                     //MSB is 0 so output high
                                     SR_RowSerLow();
                                  }

                                  SR_RowPulse();  //Pulse the Clock line
                                  data = data << 1;  //Now bring next bit at MSB position
                               }
                               break;

        case SR_RowLatchHigh    :   SR_ROW_PORT |= (1 << SR_ROW_RCLK); // High
                                    break;

        case SR_RowLatchLow    :   SR_ROW_PORT &= (~(1 << SR_ROW_RCLK)); // Low
                                   break;

        default             :   break;
    }
    
    return state;
}

#endif //__SHIFTREGROWSM_H__
