#ifndef __SHIFTREGMC2_H__
#define __SHIFTREGMC2_H__

#include "ShiftRegScoreSM.h"

void SRInit()
{
	// Make the Serial, shift register clock, register clock lines output
    SR_SCORE_DDR |= ((1 << SR_SCORE_SRCLK) | (1 << SR_SCORE_RCLK) | (1 << SR_SCORE_SER));
}

#endif //__SHIFTREGMC2_H__
