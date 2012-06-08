#ifndef __PINMAP_H__
#define __PINMAP_H__

/********************* Shift Register Pin Map *********************/

// LED Matrix SR for rows
#define SR_ROW_PORT		PORTA
#define SR_ROW_DDR		DDRA

#define SR_ROW_SER		PA0
#define SR_ROW_RCLK		PA1
#define SR_ROW_SRCLK	PA2

// LED Matrix SR for columns
#define SR_COL_PORT		PORTB
#define SR_COL_DDR		DDRB

#define SR_COL_SER		PB0
#define SR_COL_RCLK		PB1
#define SR_COL_SRCLK	PB2

// SR for piece
#define SR_PIECE_PORT	PORTC
#define SR_PIECE_DDR	DDRC

#define SR_PIECE_SER	PC0
#define SR_PIECE_RCLK	PC1
#define SR_PIECE_SRCLK	PC2

// SR for score
#define SR_SCORE_PORT	PORTA
#define SR_SCORE_DDR	DDRA

#define SR_SCORE_SER	PA0
#define SR_SCORE_RCLK	PA1
#define SR_SCORE_SRCLK	PA2

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
