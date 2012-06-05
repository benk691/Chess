#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <avr/io.h>

unsigned char rowData = 0x00;
unsigned long colData = 0x0000;

unsigned char reset = 0;

unsigned char LM_rdy = 0;

unsigned char SR_RowSend = 0;
unsigned char SR_RowRdy = 0;

unsigned char SR_ColSend = 0;
unsigned char SR_ColRdy = 0;

/*
const unsigned char ROW_ID = 'R';
#define ROW_MACRO(m)	SR_ROW_##m
#define ROW_FUNCT(f)	SR_Row##f

const unsigned char COL_ID = 'C';
#define COL_MACRO(m)	SR_COL_##m
#define COL_FUNCT(f)	SR_Col##f
*/

#endif //__GENERAL_H__
