#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

enum turns { WHITE, BLACK } turn;

const unsigned char matrix_size = 9;
const unsigned char extra = 1;

unsigned char rowData = 0x00;
unsigned long colData = 0x0000;

unsigned char reset = 0;

unsigned char Move_Row = 0;
unsigned char Move_Col = 0;
unsigned char Move_RowSend = 0;
unsigned char Move_ColSend = 0;

unsigned char SR_RowSend = 0;
unsigned char SR_ColSend = 0;

unsigned char LM_enable_unique = 0;
unsigned char LM_unique_row = 0;
unsigned char LM_unique_col= 0;

unsigned char LCD_rdy_g = 0;  // Set by user synchSM wishing to display string in LCD_string_g
unsigned char LCD_go_g = 0;  // Set by user synchSM wishing to display string in LCD_string_g

unsigned char LCD_string_g[17]; // Filled by user synchSM, 16 chars plus end-of-string char

unsigned char old_key = '\0';
unsigned char key = '\0';

unsigned char row[ 9 ];

unsigned long col[ 9 ];

/*--------Bit-access functions -----------------------------------------------*/
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}
/*--------END bit-access functions -------------------------------------------*/

#endif //__GENERAL_H__
