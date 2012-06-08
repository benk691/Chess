#ifndef __SCOREDISPLAYSM_H__
#define __SCOREDISPLAYSM_H__

#include "ShiftRegWScoreSM.h"
#include "ShiftRegBScoreSM.h"

enum ScoreDisplayStates { Score_Init, Score_Display } ScoreDisplayState;

void scoreDisplay();

int ScoreDisplay_Tick(int state)
{
    // Transitions
    switch(state)
    {
        case -1:
            state = Score_Init;
            break;

        case Score_Init:
            state = Score_Display;
            break;

        case Score_Display:
            state = Score_Display;
            break;

        default :   break;
            
    }

    //Actions
    switch(state)
    {
        case Score_Init:
            whiteScore = 0x00;
            blackScore = 0x00;
            SR_WScoreSend = 1;
            SR_BScoreSend = 1;
            break;

        case Score_Display:
			//scoreDisplay();
			whiteScore = 0x7E;
            SR_WScoreSend = 1;
            SR_BScoreSend = 1;
            break;

        default :   break;
            
    }

    return state;
}

void scoreDisplay()
{
	unsigned char wScore = 0x00;
	unsigned char bScore = 0x00;
	
    switch(whiteScore)
    {
         case 0	:	wScore = 0x7E;
					break;
		 case 1	:	wScore = 0x12;
					break;
		 case 2	:	wScore = 0x3D;
					break;
		 case 3	:	wScore = 0x37;
					break;
		 case 4	:	wScore = 0x53;
					break;
		 case 5	:	wScore = 0x67;
					break;
		 case 6	:	wScore = 0x6F;
					break;
		 case 7	:	wScore = 0x32;
					break;
		 case 8	:	wScore = 0x7F;
					break;
		 case 9	:	wScore = 0x77;
					break;
		 default:	wScore = 0x00;
					break;
    }
	
	switch(blackScore)
    {
         case 0	:	bScore = 0x7E;
					break;
		 case 1	:	bScore = 0x12;
					break;
		 case 2	:	bScore = 0x3D;
					break;
		 case 3	:	bScore = 0x37;
					break;
		 case 4	:	bScore = 0x53;
					break;
		 case 5	:	bScore = 0x67;
					break;
		 case 6	:	bScore = 0x6F;
					break;
		 case 7	:	bScore = 0x32;
					break;
		 case 8	:	bScore = 0x7F;
					break;
		 case 9	:	bScore = 0x77;
					break;
		 default:	bScore = 0x00;
					break;
    }
    
    whiteScore = wScore;
    blackScore = bScore;
}

#endif //__SCOREDISPLAYSM_H__
