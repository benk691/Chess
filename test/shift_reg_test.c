/*
 * shift_reg_test.c
 *
 * Created: 5/30/2012 5:51:17 AM
 *  Author: Embedded Systems Lab
 */ 

#include <avr/io.h>
#include <util/delay.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b)
{
    return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

unsigned char GetBit(unsigned char x, unsigned char k)
{
    return ((x & (0x01 << k)) != 0);
}

#define SR_PORT		PORTA
#define SR_DDR		DDRA

#define SR_SER		PA0
#define SR_RCLK	    PA1
#define SR_SRCLK    PA2

void SRSerHigh()
{
	SR_PORT |= (1 << SR_SER);
}	

void SRSerLow()
{
	SR_PORT &= (~(1 << SR_SER));
}

void SRInit()
{
	// Make the Serial, shift register clock, register clock lines output
	SR_DDR |= ((1 << SR_SRCLK) | (1 << SR_RCLK) | (1 << SR_SER));
}

void SRPulse()
{
	SR_PORT |= (1 << SR_SRCLK); //High
	
	SR_PORT &= (~(1 << SR_SRCLK)); // Low
}

void SRLatch()
{
	SR_PORT |= (1 << SR_RCLK); //High
	_delay_loop_1(1);
	
	SR_PORT &= (~(1 << SR_RCLK)); // Low
	_delay_loop_1(1);
}

/*
Main High level function to write a single byte to
Output shift register. 

Arguments:
   single byte to write to the IC

Returns:
   NONE

Description:
   The byte is serially transfered to shift register
   and then latched. The byte is then available on
   output line Q0 to Q7 of the IC.
*/
void SRWrite(unsigned char data)
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
         SRSerHigh();
      }
      else
      {
         //MSB is 0 so output high
         SRSerLow();
      }

      SRPulse();  //Pulse the Clock line
      data = data << 1;  //Now bring next bit at MSB position

   }

   //Now all 8 bits have been transferred to shift register
   //Move them to output latch at one
   SRLatch();
}

/*
Simple Delay function approx 0.5 seconds
*/
void Wait()
{
   for(unsigned char i = 0; i < 30; i++)
   {
      _delay_loop_2(0);
   }
}

int main(void)
{
	unsigned char led_pattern[9]={
                        0x00,
						0x01,
						0x02,
						0x04,
						0x08,
						0x10,
						0x20,
						0x40,
						0x80
                     };
	SRInit();
	
    while(1)
    {
		for(unsigned char i = 0; i < 9; i++)
		{
			SRWrite(led_pattern[i]);   //Write the data to SR
			Wait();                 //Wait 
		}
    }
}
