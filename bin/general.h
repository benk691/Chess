#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

const unsigned char matrix_size = 8;

unsigned char rowData = 0x00;
unsigned long colData = 0x0000;

unsigned char reset = 0;

unsigned char SR_RowSend = 0;

unsigned char SR_ColSend = 0;

unsigned char LCD_go_g = 0;  // Set by user synchSM wishing to display string in LCD_string_g

unsigned char LCD_string_g[17]; // Filled by user synchSM, 16 chars plus end-of-string char

unsigned char old_key = '\0';
unsigned char key = '\0';

unsigned char row[ 8 ] =
{
	0xFE,  //1111 1110
	0xFD,  //1111 1101
	0xFB,  //1111 1011
	0xF7,  //1111 0111
	0xEF,  //1110 1111
	0xDF,  //1101 1111
	0xBF,  //1011 1111
	0x7F,  //0111 1111 
};

unsigned long col[ 8 ] =
{
	0x03C0,		//GG BB BB RR
	0x03C0,		//GG BB BB RR
	0x03C0,		//GG BB BB RR
	0x03C0,		//GG BB BB RR
	0x03C0,		//GG BB BB RR
	0x03C0,		//GG BB BB RR
	0x03C0,		//GG BB BB RR
	0x03C0		//GG BB BB RR
};

/*--------Bit-access functions -----------------------------------------------*/
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}
/*--------END bit-access functions -------------------------------------------*/

#endif //__GENERAL_H__
