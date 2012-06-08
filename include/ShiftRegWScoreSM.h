#ifndef __SHIFTREGWSCORESM_H__
#define __SHIFTREGWSCORESM_H__

#include "general.h"
#include "PinMap.h"

enum SR_WScoreStates { SR_WScoreInit, SR_WScoreWait, SR_WScoreWrite } SR_WScoreState;

int SR_WScoreTick(int state)
{
    static unsigned char oldData = 0x00;
    static unsigned char data = 0x00;

    // Transitions
    switch(state)
    {
        case -1     :   state = SR_WScoreInit;
                        break;
        
        case SR_WScoreInit : state = SR_WScoreWait;
                            break;

        case SR_WScoreWait : if(!SR_WScoreSend)
                            {
                                state = SR_WScoreWait;
                            }
                            else
                            {
                                oldData = whiteScore;
                                data = whiteScore;
                                state = SR_WScoreWrite;
                            }
                            break;
        
        case SR_WScoreWrite    :  state = SR_WScoreWait;
                                 break;

        default             :   break;
    }

    // State Actions
    switch(state)
    {
        case -1     :   break;

        case SR_WScoreInit :   SR_WScoreSend = 0;
                              break;

        case SR_WScoreWait :   break;
        
        case SR_WScoreWrite    :  for(unsigned char i = 0; i < 8; i++)
                                {
                                    // Output the data on DS line according to the
                                    // Value of MSB
                                    if(data & 0x80)
                                    {
                                        // MSB is 1 so output high
                                        SR_WSCORE_PORT |= (1 << SR_WSCORE_SER); // High
                                    }
                                    else
                                    {
                                        // MSB is 0 so output low
                                        SR_WSCORE_PORT &= (~(1 << SR_WSCORE_SER)); // Low
                                    }

                                    //Pulse the Clock line
                                    SR_WSCORE_PORT |= (1 << SR_WSCORE_SRCLK); //High

                                    SR_WSCORE_PORT &= (~(1 << SR_WSCORE_SRCLK)); // Low

                                    data = data << 1;  //Now bring next bit at MSB position
                                }
								
								SR_WSCORE_PORT |= (1 << SR_WSCORE_RCLK); // High
								asm("nop");
								
								SR_WSCORE_PORT &= (~(1 << SR_WSCORE_RCLK)); // Low
								asm("nop");
								
								SR_WScoreSend = 0;
                                break;

        default             :   break;
    }
    
    return state;
}

#endif //__SHIFTREGWSCORESM_H__
