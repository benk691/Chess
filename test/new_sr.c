/*
 * project.c
 *
 * Created: 6/1/2012 9:34:07 AM
 *  Author: Embedded Systems Lab
 */ 

#include <avr/io.h>

#define DDR_SPI		DDRB
#define DD_MOSI		5
#define DD_SCK		7

void SPI_MasterInit()
{
	DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK);
	//SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	SPCR = 0x52;
}

void SPI_MasterTransmit(char cData)
{
	SPDR = cData;
	while(!(SPSR & (1 << SPIF)));
}

int main(void)
{
	SPI_MasterInit();
	
	DDRA = 0x01;
	DDRB |= 0x01;
	
    while(1)
    {
		PORTA &= 0xFE;
		SPI_MasterTransmit(0x00);
		PORTA |= 0x01;
		
		PORTB &= 0xFE;
		SPI_MasterTransmit(0xA8);
		PORTB |= 0x01;
		
    }
}

/*
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b)
{
    return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

unsigned char GetBit(unsigned char x, unsigned char k)
{
    return ((x & (0x01 << k)) != 0);
}
*/
//#include <util/delay.h>
/*
void Transmit(unsigned char port, unsigned char pin, unsigned char cData)
{
	switch(port)
	{
		case 'A'	:	
		case 'a'	:   PORTA = SetBit(PORTA, pin, 0);
						SPI_MasterTransmit(cData);
						PORTA = SetBit(PORTA, pin, 1);
						break;
		case 'B'	:	
		case 'b'	:	PORTB = SetBit(PORTB, pin, 0);
						SPI_MasterTransmit(cData);
						PORTB = SetBit(PORTB, pin, 1);
						break;
		case 'C'	:	
		case 'c'	:	PORTC = SetBit(PORTC, pin, 0);
						SPI_MasterTransmit(cData);
						PORTC = SetBit(PORTC, pin, 1);
						break;
		case 'D'	:	
		case 'd'	:	PORTD = SetBit(PORTD, pin, 0);
						SPI_MasterTransmit(cData);
						PORTD = SetBit(PORTD, pin, 1);
						break;
		default		:	break;
	}
}
*/
/*
void Wait()
{
   for(unsigned char i = 0; i < 30; i++)
   {
      _delay_loop_2(0);
   }
}
*/