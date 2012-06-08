#ifndef __SOUNDSM_H__
#define __SOUNDSM_H__

#include "general.h"
#include "PinMap.h"

enum SoundStates { Sound_Wait, Sound_Low, Sound_High } SoundState;

int Sound_Tick(int state)
{
    // Transitions
    switch(state)
    {
        case -1:
            SOUND_PORT = SetBit(SOUND_PORT, SOUND_PIN, 0);
            state = Sound_Wait;
            break;

        case Sound_Wait:
            if(sound_on)
            {
                state = Sound_Low;
            }
            else
            {
                SOUND_PORT = SetBit(SOUND_PORT, SOUND_PIN, 0);
                state = Sound_Wait;
            }
            break;
        case Sound_Low:
            if(sound_on)
            {
                state = Sound_High;
            }
            else
            {
                SOUND_PORT = SetBit(SOUND_PORT, SOUND_PIN, 0);
                state = Sound_Wait;
            }
            break;

        case Sound_High:
            if(sound_on)
            {
                state = Sound_Low;
            }
            else
            {
                SOUND_PORT = SetBit(SOUND_PORT, SOUND_PIN, 0);
                state = Sound_Wait;
            }
            break;

        default :   break;
            
    }

    //Actions
    switch(state)
    {
        case Sound_Wait:
            break;

        case Sound_Low:
            SOUND_PORT = SetBit(SOUND_PORT, SOUND_PIN, 0);
            break;

        case Sound_High:
            SOUND_PORT = SetBit(SOUND_PORT, SOUND_PIN, 1);
            break;

        default :   break;
            
    }

    return state;
}

#endif //__SOUNDSM_H__
