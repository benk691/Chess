#ifndef __SHIFTREGCOLSM_H__
#define __SHIFTREGCOLSM_H__

#include <util/delay.h>
#include "general.h"
#include "PinMap.h"

enum SR_ColStates { SR_ColWait, SR_ColWrite, SR_ColLatchHigh, SR_ColLatchLow } SR_ColState;

void SR_ColSerHigh()
{
	SR_COL_PORT |= (1 << SR_COL_SER);
}	

void SR_ColSerLow()
{
	SR_COL_PORT &= (~(1 << SR_COL_SER));
}

int SR_Tick(int state)
{
    static unsigned char data = 0x00;

    // Transitions
    switch(state)
    {
        case -1     :   state = SR_ColWait;
                        break;

        case SR_ColWait :   if(!SR_ColSend)
                            {
                                state = SR_ColWait;
                            }
                            else
                            {
                                data = rowData;
                                state = SR_ColWrite;
                            }
                            break;
        
        case SR_ColWrite    :  state = SR_ColLatchHigh;
                               break;

        case SR_ColLatchHigh    :   state = SR_ColLatchLow;
                                    break;

        case SR_ColLatchLow    :   state = SR_ColWait;
                                   break;

        default             :   break;
    }

    // State Actions
    switch(state)
    {
        case -1     :   break;

        case SR_ColWait :   break;
        
        case SR_ColWrite    :  for(unsigned char i = 0; i < 8; i++)
                               {
                                  //Output the data on DS line according to the
                                  //Value of MSB
                                  if(data & 0x80)
                                  {
                                     //MSB is 1 so output high
                                     SR_ColSerHigh();
                                  }
                                  else
                                  {
                                     //MSB is 0 so output high
                                     SR_ColSerLow();
                                  }

                                  SR_ColPulse();  //Pulse the Clock line
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
