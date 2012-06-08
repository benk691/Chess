#ifndef __SHIFTREG_H__
#define __SHIFTREG_H__

#include "ShiftRegRowSM.h"
#include "ShiftRegColSM.h"
#include "ShiftRegPieceSM.h"

void SRInit()
{
	// Make the Serial, shift register clock, register clock lines output
	SR_ROW_DDR |= ((1 << SR_ROW_SRCLK) | (1 << SR_ROW_RCLK) | (1 << SR_ROW_SER));
	SR_COL_DDR |= ((1 << SR_COL_SRCLK) | (1 << SR_COL_RCLK) | (1 << SR_COL_SER));
    SR_PIECE_DDR |= ((1 << SR_PIECE_SRCLK) | (1 << SR_PIECE_RCLK) | (1 << SR_PIECE_SER));
}

#endif //__SHIFTREG_H__
