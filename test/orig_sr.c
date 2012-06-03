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
/*
struct ShiftReg
{
	unsigned char _port;
	unsigned char _ser;
	unsigned char _rclk;
	unsigned char _srclk;
	
	ShiftReg(unsigned char p = 'A', unsigned char s = 0, unsigned char r = 1, 
			 unsigned char sr = 2)
	{}
	
	unsigned char port()
	{
		unsigned char p = 0;
		
		switch(_port)
		{
			case 'A'	:	
			case 'a'	:   p = PORTA;
							break;
			case 'B'	:	
			case 'b'	:	p = PORTB;
							break;
			case 'C'	:	
			case 'c'	:	p = PORTC;
							break;
			case 'D'	:	
			case 'd'	:	p = PORTD;
							break;
			default:	:	break;
		}
		
		return p;
	}
};
*/

#define SR1_PORT	PORTA
#define SR1_DDR		DDRA

#define SR1_SER		PA0
#define SR1_RCLK	PA1
#define SR1_SRCLK   PA2

#define SR2_PORT	PORTB
#define SR2_DDR		DDRB

#define SR2_SER		PB0
#define SR2_RCLK	PB1
#define SR2_SRCLK   PB2

void SR1SerHigh()
{
	SR1_PORT |= (1 << SR1_SER);
}	

void SR1SerLow()
{
	SR1_PORT &= (~(1 << SR1_SER));
}

void SR2SerHigh()
{
	SR2_PORT |= (1 << SR2_SER);
}	

void SR2SerLow()
{
	SR2_PORT &= (~(1 << SR2_SER));
}

void SRInit()
{
	// Make the Serial, shift register clock, register clock lines output
	SR1_DDR |= ((1 << SR1_SRCLK) | (1 << SR1_RCLK) | (1 << SR1_SER));
	SR2_DDR |= ((1 << SR2_SRCLK) | (1 << SR2_RCLK) | (1 << SR2_SER));
}

void SR1Pulse()
{
	SR1_PORT |= (1 << SR1_SRCLK); //High
	
	SR1_PORT &= (~(1 << SR1_SRCLK)); // Low
}

void SR1Latch()
{
	SR1_PORT |= (1 << SR1_RCLK); //High
	_delay_loop_1(1);
	
	SR1_PORT &= (~(1 << SR1_RCLK)); // Low
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
void SR1Write8(unsigned char data)
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
         SR1SerHigh();
      }
      else
      {
         //MSB is 0 so output high
         SR1SerLow();
      }

      SR1Pulse();  //Pulse the Clock line
      data = data << 1;  //Now bring next bit at MSB position

   }

   //Now all 8 bits have been transferred to shift register
   //Move them to output latch at one
   SR1Latch();
}

void SR1Write16(unsigned long data)
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
         SR1SerHigh();
      }
      else
      {
         //MSB is 0 so output high
         SR1SerLow();
      }

      SR1Pulse();  //Pulse the Clock line
      data = data << 1;  //Now bring next bit at MSB position

   }

   //Now all 8 bits have been transferred to shift register
   //Move them to output latch at one
   SR1Latch();
}

void SR2Pulse()
{
	SR2_PORT |= (1 << SR2_SRCLK); //High
	
	SR2_PORT &= (~(1 << SR2_SRCLK)); // Low
}

void SR2Latch()
{
	SR2_PORT |= (1 << SR2_RCLK); //High
	_delay_loop_1(1);
	
	SR2_PORT &= (~(1 << SR2_RCLK)); // Low
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
void SR2Write8(unsigned char data)
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
         SR2SerHigh();
      }
      else
      {
         //MSB is 0 so output high
         SR2SerLow();
      }

      SR2Pulse();  //Pulse the Clock line
      data = data << 1;  //Now bring next bit at MSB position

   }

   //Now all 8 bits have been transferred to shift register
   //Move them to output latch at one
   SR2Latch();
}

void SR2Write16(unsigned long data)
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
         SR2SerHigh();
      }
      else
      {
         //MSB is 0 so output high
         SR2SerLow();
      }

      SR2Pulse();  //Pulse the Clock line
      data = data << 1;  //Now bring next bit at MSB position

   }

   //Now all 8 bits have been transferred to shift register
   //Move them to output latch at one
   SR2Latch();
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
	unsigned long s1_numb[] =
	{
		0x3000,
		0x0300,
		0x0030,
		0x0003
	};
	unsigned long s2_numb[] =
	{
		0x2000,
		0x0200,
		0x00F0,
		0x0002
	};
	
	const int size1 = sizeof(s1_numb)/sizeof(unsigned long);
	const int size2 = sizeof(s2_numb)/sizeof(unsigned long);
	
	SRInit();
	
    while(1)
    {
		for(int i = 0; i < size1; i++)
		{
			SR1Write16(s1_numb[i]);
			Wait();                 //Wait 
		}
		SR1Write16(0x0000);
		for(int i = 0; i < size2; i++)
		{
			SR2Write16(s2_numb[i]);
			Wait();                 //Wait 
		}
		SR2Write16(0x0000);
		for(int i = 0; i < size1; i++)
		{
			SR1Write16(s1_numb[i]);
			SR2Write16(s2_numb[i]);
			Wait();                 //Wait 
		}
		SR1Write16(0x0000);
		SR2Write16(0x0000);
    }
}
