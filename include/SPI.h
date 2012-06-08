#ifndef __SPI_H__
#define __SPI_H__

#include "general.h"
#include "PinMap.h"

void SPI_MasterInit()
{
	DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK);
	//SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	SPCR = 0x52;
}

void SPI_MasterTransmit(unsigned char cData)
{
	SPDR = cData;
	while(!(SPSR & (1 << SPIF)));
}

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
#endif //__SPI_H__
