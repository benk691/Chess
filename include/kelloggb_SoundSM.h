/*
 * kelloggb_SoundSM.h - 06/08/2012
 * Name & E-mail: Benjamin Kellogg kelloggb@cs.ucr.edu
 * CS Login: kelloggb
 * Partner(s) Name & E-mail: Gabriel Limon glimo002@ucr.edu
 * Lab Section: 021
 * Assignment: Lab Project
 * Project Description: This game is based off of chess, but is more like guessing 
 * 	which locations have positive or negative points.
 * 
 * I acknowledge all content contained herein is my own original work.
 */
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
