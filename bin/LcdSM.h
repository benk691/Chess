#ifndef __LCDSM_H__
#define __LCDSM_H__

#include "general.h"
#include "PinMap.h"

// Define LCD port assignments here so easier to change than if hardcoded below
unsigned char *LCD_Data = &LCD_DATA_PORT; // LCD 8-bit data bus
unsigned char *LCD_Ctrl = &LCD_CTRL_PORT; // LCD needs 2-bits for control, use port B
const unsigned char LCD_RS = LCD_RESET_PIN;     // LCD Reset pin is PD2
const unsigned char LCD_E = LCD_ENABLE_PIN;      // LCD Enable pin is PD3

void LCD_WriteCmdStart(unsigned char cmd)
{
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_RS, 0);
	*LCD_Data = cmd;
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 1);
}
void LCD_WriteCmdEnd() {
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 0);
}
void LCD_WriteDataStart(unsigned char Data)
{
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_RS,1);
	*LCD_Data = Data;
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 1);
}
void LCD_WriteDataEnd()
{
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 0);
}
void LCD_Cursor(unsigned char column)
{
	if ( column < 8 ) {
		LCD_WriteCmdStart(0x80+column);
	}
	else {
		LCD_WriteCmdStart(0xB8+column);
	}
}

enum LI_States { LI_Init1, LI_Init2, LI_Init3, LI_Init4, LI_Init5, LI_Init6,
		LI_WaitDisplayString, LI_Clr, LI_PositionCursor,
		LI_DisplayChar, LI_WaitGo0 };

int LCDI_SMTick(int state)
{
	static unsigned char i;
	
	switch(state) 
	{ // Transitions
		case -1:
			state = LI_Init1;
			break;
		case LI_Init1:
			state = LI_Init2;
			i=0;
			break;
		case LI_Init2:
			if (i<10) { // Wait 100 ms after power up
				state = LI_Init2;
			}
			else {
				state = LI_Init3;
			}
			break;
		case LI_Init3:
			if (1) {
				state = LI_Init4;
				LCD_WriteCmdEnd();
			}
			break;
		case LI_Init4:
			if (1) {
				state = LI_Init5;
				LCD_WriteCmdEnd();
			}
			break;
		case LI_Init5:
			if (1) {
				state = LI_Init6;
				LCD_WriteCmdEnd();
			}
			break;
		case LI_Init6:
			if (1) {
				state = LI_WaitDisplayString;
				LCD_WriteCmdEnd();
			}
			break;
		case LI_WaitDisplayString:
			if (!LCD_go_g) {
				state = LI_WaitDisplayString;
			}
			else if (LCD_go_g) {
				LCD_rdy_g = 0;
				state = LI_Clr;
			}
			break;
		case LI_Clr:
			if (1) {
				state = LI_PositionCursor;
				LCD_WriteCmdEnd();
				i=0;
			}
			break;
		case LI_PositionCursor:
			if (1) {
				state = LI_DisplayChar;
				LCD_WriteCmdEnd();
			}
			break;
		case LI_DisplayChar:
			if (i<16) {
				state = LI_PositionCursor;
				LCD_WriteDataEnd();
				i++;
			}
			else {
				state = LI_WaitGo0;
				LCD_WriteDataEnd();
			}
			break;
		case LI_WaitGo0:
			if (!LCD_go_g) {
				state = LI_WaitDisplayString;
			}
			else if (LCD_go_g) {
				state = LI_WaitGo0;
			}
			break;
		default:
			state = LI_Init1;
	} // Transitions

	switch(state) 
	{ // State actions
		case LI_Init1:
			LCD_rdy_g = 0;
			break;
		case LI_Init2:
			i++; // Waiting after power up
			break;
		case LI_Init3:
			LCD_WriteCmdStart(0x38);
			break;
		case LI_Init4:
			LCD_WriteCmdStart(0x06);
			break;
		case LI_Init5:
			LCD_WriteCmdStart(0x0F);
			break;
		case LI_Init6:
			LCD_WriteCmdStart(0x01); // Clear
			break;
		case LI_WaitDisplayString:
			LCD_rdy_g = 1;
			break;
		case LI_Clr:
			LCD_WriteCmdStart(0x01);
			break;
		case LI_PositionCursor:
			LCD_Cursor(i);
			break;
		case LI_DisplayChar:
			LCD_WriteDataStart(LCD_string_g[i]);
			break;
		case LI_WaitGo0:
			break;
		default:
			break;
	} // State actions
	return state;
}

#endif //__LCDSM_H__
