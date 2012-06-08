#ifndef __SCOREDISPLAYMC1_H__
#define __SCOREDISPLAYMC1_H__

#include "general.h"
#include "PinMap.h"

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
            whiteScore = 0;
            break;

        case Score_Display:
			scoreDisplay();
            break;

        default :   break;
            
    }

    return state;
}

void scoreDisplay()
{
    switch(whiteScore)
    {
         case 0	:	PORTA = 0x7E;
					break;
		 case 1	:	PORTA = 0x12;
					break;
		 case 2	:	PORTA = 0x3D;
					break;
		 case 3	:	PORTA = 0x37;
					break;
		 case 4	:	PORTA = 0x53;
					break;
		 case 5	:	PORTA = 0x67;
					break;
		 case 6	:	PORTA = 0x6F;
					break;
		 case 7	:	PORTA = 0x32;
					break;
		 case 8	:	PORTA = 0x7F;
					break;
		 case 9	:	PORTA = 0x77;
					break;
		 default:	PORTA = 0x00;
					break;
    }
}

#endif //__SCOREDISPLAYMC1_H__
