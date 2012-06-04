#ifndef __SHIFTREG_H__
#define __SHIFTREG_H__

#include <util/delay.h>
#include "general.h"
#include "PinMap.h"

void SRInit()
{
	// Make the Serial, shift register clock, register clock lines output
	SR_ROW_DDR |= ((1 << SR_ROW_SRCLK) | (1 << SR_ROW_RCLK) | (1 << SR_ROW_SER));
	SR_COL_DDR |= ((1 << SR_COL_SRCLK) | (1 << SR_COL_RCLK) | (1 << SR_COL_SER));
}

void SR_RowSerHigh()
{
	SR_ROW_PORT |= (1 << SR_ROW_SER);
}	

void SR_RowSerLow()
{
	SR_ROW_PORT &= (~(1 << SR_ROW_SER));
}

void SR_ColSerHigh()
{
	SR_COL_PORT |= (1 << SR_COL_SER);
}

void SR_ColSerLow()
{
	SR_COL_PORT &= (~(1 << SR_COL_SER));
}

void SR_RowPulse()
{
	SR_ROW_PORT |= (1 << SR_ROW_SRCLK); //High
	
	SR_ROW_PORT &= (~(1 << SR_ROW_SRCLK)); // Low
}

void SR_RowLatch()
{
	SR_ROW_PORT |= (1 << SR_ROW_RCLK); //High
	_delay_loop_1(1);
	
	SR_ROW_PORT &= (~(1 << SR_ROW_RCLK)); // Low
	_delay_loop_1(1);
}

void SR_ColPulse()
{
	SR_COL_PORT |= (1 << SR_COL_SRCLK); //High
	
	SR_COL_PORT &= (~(1 << SR_COL_SRCLK)); // Low
}

void SR_ColLatch()
{
	SR_COL_PORT |= (1 << SR_COL_RCLK); //High
	_delay_loop_1(1);
	
	SR_COL_PORT &= (~(1 << SR_COL_RCLK)); // Low
	_delay_loop_1(1);
}

void SR_RowWrite(unsigned char data)
{
   //Send each 8 bits serially

   //Order is MSB first
   for(unsigned char i = 0; i < 8; i++)
   {
      //Output the data on DS line according to the
      //Value of MSB
      if(data & 0x80)
      {
         //MSB is 1 so output high
         SR_RowSerHigh();
      }
      else
      {
         //MSB is 0 so output high
         SR_RowSerLow();
      }

      SR_RowPulse();  //Pulse the Clock line
      data = data << 1;  //Now bring next bit at MSB position

   }

   //Now all 8 bits have been transferred to shift register
   //Move them to output latch at one
   SR_RowLatch();
}

void SR_ColWrite(unsigned long data)
{
   //Send each 8 bits serially

   //Order is MSB first
   for(unsigned char i = 0; i < 16; i++)
   {
      //Output the data on DS line according to the
      //Value of MSB
      if(data & 0x8000)
      {
         //MSB is 1 so output high
         SR_ColSerHigh();
      }
      else
      {
         //MSB is 0 so output high
         SR_ColSerLow();
      }

      SR_ColPulse();  //Pulse the Clock line
      data = data << 1;  //Now bring next bit at MSB position

   }

   //Now all 8 bits have been transferred to shift register
   //Move them to output latch at one
   SR_ColLatch();
}

#endif //__SHIFTREG_H__