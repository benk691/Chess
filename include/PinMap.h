#ifndef __PINMAP_H__
#define __PINMAP_H__

/********************* SPI Pin Map *********************/

#define SPI_DDR	    DDRB
#define SPI_MOSI    5
#define SPI_SCK     7

/*******************************************************/
/********************* Shift Register Pin Map *********************/

// LED Matrix SR for rows
#define SR_ROW_PORT		PORTC
#define SR_ROW_RCLK		4

// LED Matrix SR for columns
#define SR_COL_PORT		PORTB
#define SR_COL_RCLK		1

// SR for piece
#define SR_PIECE_PORT	PORTD
#define SR_PIECE_RCLK	3

/******************************************************************/
/********************* 7-Seg Pin Map *********************/

#define WSEG_PORT	PORTA
#define BSEG_PORT	PORTA

/*********************************************************/
/********************* Sound Pin Map *********************/

#define SOUND_PORT	PORTA
#define SOUND_PIN	7

/*********************************************************/

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
