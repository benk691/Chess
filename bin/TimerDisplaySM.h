#ifndef __TIMERDISPLAYSM_H__
#define __TIMERDISPLAYSM_H__

#include "general.h"
#include "PinMap.h"

enum TimerDisplayStates { Timer_Init_Wait, Timer_Display, Timer_NGo } TimerDisplayState;

int TimerDisplay_Tick(int state)
{
    unsigned char i = 0;

    // Transitions
    switch(state)
    {
        case Timer_Init_Wait:
            if(!LCD_rdy_g)
            {
                state = Timer_Init_Wait;
            }
            else
            {
                state = Timer_Display;
            }
            break;

        case Timer_Display:
            state = Timer_NGo;
            break;

        case Timer_NGo:
            state = Timer_Init_Wait;
            break;

        default :   break;
            
    }

    //Actions
    switch(state)
    {
        case Timer_Init_Wait    :   break;

        case Timer_Display:
			if(key != '\0')
			{
				for (i = 0; i < 16; i++)
				{
					if(key >= 1 && key <= 8)
					{
						LCD_string_g[i] = (char)(key + (int)('0'));
					}
					else
					{
						LCD_string_g[i] = key;	
					}
				}
				LCD_string_g[i] = '\0';
				LCD_go_g = 1;
			}			
            break;

        case Timer_NGo:
            LCD_go_g = 0;
            break;

        default :   break;
            
    }

    return state;
}

#endif //__TIMERDISPLAYSM_H__
