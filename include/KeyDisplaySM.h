#ifndef __KEYDISPLAYSM_H__
#define __KEYDISPLAYSM_H__

#include "general.h"
#include "PinMap.h"

enum KeyDisplayStates { Key_Init_Wait, Key_Display, Key_NGo } KeyDisplayState;

int KeyDisplay_Tick(int state)
{
    unsigned char i = 0;

    // Transitions
    switch(state)
    {
        case Key_Init_Wait:
            if(!LCD_rdy_g)
            {
                state = Key_Init_Wait;
            }
            else
            {
                state = Key_Display;
            }
            break;

        case Key_Display:
            state = Key_NGo;
            break;

        case Key_NGo:
            state = Key_Init_Wait;
            break;

        default :   break;
            
    }

    //Actions
    switch(state)
    {
        case Key_Init_Wait    :   break;

        case Key_Display:
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

        case Key_NGo:
            LCD_go_g = 0;
            break;

        default :   break;
            
    }

    return state;
}

#endif //__KEYDISPLAYSM_H__
