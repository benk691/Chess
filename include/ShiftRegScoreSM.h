#ifndef __SHIFTREGSCORESM_H__
#define __SHIFTREGSCORESM_H__

#include "general.h"
#include "PinMap.h"

enum SR_ScoreStates { SR_ScoreInit, SR_ScoreWait, SR_ScoreWrite } SR_ScoreState;

int SR_ScoreTick(int state)
{
    static unsigned char oldData = 0x00;
    static unsigned char data = 0x00;

    // Transitions
    switch(state)
    {
        case -1     :   state = SR_ScoreInit;
                        break;
        
        case SR_ScoreInit : state = SR_ScoreWait;
                            break;

        case SR_ScoreWait : if(!SR_ScoreSend)
                            {
                                state = SR_ScoreWait;
                            }
                            else
                            {
                                oldData = scoreData;
                                data = scoreData;
                                state = SR_ScoreWrite;
                            }
                            break;
        
        case SR_ScoreWrite    :  state = SR_ScoreWait;
                                 break;

        default             :   break;
    }

    // State Actions
    switch(state)
    {
        case -1     :   break;

        case SR_ScoreInit :   SR_ScoreSend = 0;
                              break;

        case SR_ScoreWait :   break;
        
        case SR_ScoreWrite    :  for(unsigned char i = 0; i < 8; i++)
                                {
                                    // Output the data on DS line according to the
                                    // Value of MSB
                                    if(data & 0x80)
                                    {
                                        // MSB is 1 so output high
                                        SR_SCORE_PORT |= (1 << SR_SCORE_SER); // High
                                    }
                                    else
                                    {
                                        // MSB is 0 so output low
                                        SR_SCORE_PORT &= (~(1 << SR_SCORE_SER)); // Low
                                    }

                                    //Pulse the Clock line
                                    SR_SCORE_PORT |= (1 << SR_SCORE_SRCLK); //High

                                    SR_SCORE_PORT &= (~(1 << SR_SCORE_SRCLK)); // Low

                                    data = data << 1;  //Now bring next bit at MSB position
                                }
								
								SR_SCORE_PORT |= (1 << SR_SCORE_RCLK); // High
								asm("nop");
								
								SR_SCORE_PORT &= (~(1 << SR_SCORE_RCLK)); // Low
								asm("nop");
								
								SR_ScoreSend = 0;
                                break;

        default             :   break;
    }
    
    return state;
}

#endif //__SHIFTREGSCORESM_H__
