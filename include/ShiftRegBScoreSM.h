#ifndef __SHIFTREGBSCORESM_H__
#define __SHIFTREGBSCORESM_H__

#include "general.h"
#include "PinMap.h"

enum SR_BScoreStates { SR_BScoreInit, SR_BScoreWait, SR_BScoreWrite } SR_BScoreState;

int SR_BScoreTick(int state)
{
    static unsigned char oldData = 0x00;
    static unsigned char data = 0x00;

    // Transitions
    switch(state)
    {
        case -1     :   state = SR_BScoreInit;
                        break;
        
        case SR_BScoreInit : state = SR_BScoreWait;
                            break;

        case SR_BScoreWait : if(!SR_BScoreSend)
                            {
                                state = SR_BScoreWait;
                            }
                            else
                            {
                                oldData = blackScore;
                                data = blackScore;
                                state = SR_BScoreWrite;
                            }
                            break;
        
        case SR_BScoreWrite    :  state = SR_BScoreWait;
                                 break;

        default             :   break;
    }

    // State Actions
    switch(state)
    {
        case -1     :   break;

        case SR_BScoreInit :   SR_BScoreSend = 0;
                              break;

        case SR_BScoreWait :   break;
        
        case SR_BScoreWrite    :  for(unsigned char i = 0; i < 8; i++)
                                {
                                    // Output the data on DS line according to the
                                    // Value of MSB
                                    if(data & 0x80)
                                    {
                                        // MSB is 1 so output high
                                        SR_BSCORE_PORT |= (1 << SR_BSCORE_SER); // High
                                    }
                                    else
                                    {
                                        // MSB is 0 so output low
                                        SR_BSCORE_PORT &= (~(1 << SR_BSCORE_SER)); // Low
                                    }

                                    //Pulse the Clock line
                                    SR_BSCORE_PORT |= (1 << SR_BSCORE_SRCLK); //High

                                    SR_BSCORE_PORT &= (~(1 << SR_BSCORE_SRCLK)); // Low

                                    data = data << 1;  //Now bring next bit at MSB position
                                }
								
								SR_BSCORE_PORT |= (1 << SR_BSCORE_RCLK); // High
								asm("nop");
								
								SR_BSCORE_PORT &= (~(1 << SR_BSCORE_RCLK)); // Low
								asm("nop");
								
								SR_BScoreSend = 0;
                                break;

        default             :   break;
    }
    
    return state;
}

#endif //__SHIFTREGBSCORESM_H__
