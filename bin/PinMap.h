#ifndef __PINMAP_H__
#define __PINMAP_H__

/********************* Shift Register Pin Map *********************/

#define SR_ROW_PORT		PORTA
#define SR_ROW_DDR		DDRA

#define SR_ROW_SER		PA0
#define SR_ROW_RCLK		PA1
#define SR_ROW_SRCLK	PA2

#define SR_COL_PORT		PORTB
#define SR_COL_DDR		DDRB

#define SR_COL_SER		PB0
#define SR_COL_RCLK		PB1
#define SR_COL_SRCLK	PB2

/******************************************************************/

/********************* LCD Pin Map *********************/

#define LCD_DATA_PORT   PORTB
#define LCD_CTRL_PORT   PORTD
#define LCD_RESET_PIN	2
#define LCD_ENABLE_PIN	3

/*******************************************************/

/********************* Keypad Pin Map *********************/

#define KEYPAD_PORT PORTC
#define KEYPAD_PIN  PINC

/**********************************************************/

/********************* Replay Button Pin Map *********************/

#define REPLAY_BUTTON_PORT PINA
#define REPLAY_BUTTON_PIN  0

/*****************************************************************/

/********************* No Replay Button Pin Map *********************/

#define NREPLAY_BUTTON_PORT PINA
#define NREPLAY_BUTTON_PIN  1

/********************************************************************/

/********************* White Timer Button Button Pin Map *********************/

#define WTIMER_BUTTON_PORT PINA
#define WTIMER_BUTTON_PIN  0

/*****************************************************************************/

/********************* Black Timer Button Button Pin Map *********************/

#define BTIMER_BUTTON_PORT PINA
#define BTIMER_BUTTON_PIN  1

/*****************************************************************************/

#endif //__PINMAP_H__
