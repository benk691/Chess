#ifndef __KEYPADSM_H__
#define __KEYPADSM_H__

#include "general.h"
#include "PinMap.h"

// Returns '\0' if no key pressed, else returns char '1', '2', ... '9', 'A', ... 
// If multiple keys pressed, returns rightmost-bottommost one
// Keypad must be connected to port C
/* Keypad arrangement
        PC4 PC5 PC6 PC7   
    col  1   2   3   4   
   row 
PC0 1    1   2   3   A
PC1 2    4   5   6   B
PC2 3    7   8   9   C
PC3 4    *   0   #   D
*/

enum KeypadStates { Keypad_ReadKey } KeypadState;

int Keypad_Tick(int state)
{
    //Transitions
    switch(state)
    {
        case -1:
            state = Keypad_ReadKey;
            break;

        case Keypad_ReadKey:
            state = Keypad_ReadKey;
            break;

        default:   break;
    }

    //Actions
    switch(state)
    {
        case -1:    break;

        case Keypad_ReadKey:
		       old_key = key;				   
               
               key ='\0';
			   
               // Check keys in col 1
               KEYPAD_PORT = 0xFF; KEYPAD_PORT = SetBit(KEYPAD_PORT,4,0); // Set all col bits, then PC4 to 0
               asm("nop");
               
               if (GetBit(KEYPAD_PIN,0)==0) { key = 1; }
               if (GetBit(KEYPAD_PIN,1)==0) { key = 4; }
               if (GetBit(KEYPAD_PIN,2)==0) { key = 7; }
               if (GetBit(KEYPAD_PIN,3)==0) { key = 'h'; } // *
               
               // Check keys in col 2	
               KEYPAD_PORT = 0xFF; KEYPAD_PORT = SetBit(KEYPAD_PORT,5,0);
               asm("nop");

               if (GetBit(KEYPAD_PIN,0)==0) { key = 2; }
               if (GetBit(KEYPAD_PIN,1)==0) { key = 5; }
               if (GetBit(KEYPAD_PIN,2)==0) { key = 8; }
               if (GetBit(KEYPAD_PIN,3)==0) { key = 'g'; }
               
               // Check keys in col 3	
               KEYPAD_PORT = 0xFF; KEYPAD_PORT = SetBit(KEYPAD_PORT,6,0);
               asm("nop");

               if (GetBit(KEYPAD_PIN,0)==0) { key = 3; }
               if (GetBit(KEYPAD_PIN,1)==0) { key = 6; }
               if (GetBit(KEYPAD_PIN,2)==0) { key = 'e'; } // 9
               if (GetBit(KEYPAD_PIN,3)==0) { key = 'f'; } // #
               
               // Check keys in col 4	
               KEYPAD_PORT = 0xFF; KEYPAD_PORT = SetBit(KEYPAD_PORT,7,0);
               asm("nop");

               if (GetBit(KEYPAD_PIN,0)==0) { key = 'a'; }
               if (GetBit(KEYPAD_PIN,1)==0) { key = 'b'; }
               if (GetBit(KEYPAD_PIN,2)==0) { key = 'c'; }
               if (GetBit(KEYPAD_PIN,3)==0) { key = 'd'; }
               break;

        default:   break;
    }

    return state;
}

#endif //__KEYPADSM_H__
