/*
 * kelloggb_PinMap.h - 06/08/2012
 * Name & E-mail: Benjamin Kellogg kelloggb@cs.ucr.edu
 * CS Login: kelloggb
 * Partner(s) Name & E-mail: Gabriel Limon glimo002@ucr.edu
 * Lab Section: 021
 * Assignment: Lab Project
 * Project Description: This game is based off of chess, but is more like guessing 
 * 	which locations have positive or negative points.
 * 
 * I acknowledge all content contained herein is my own original work.
 */
#ifndef __PINMAP_H__
#define __PINMAP_H__

/********************* Shift Register Pin Map *********************/

// LED Matrix SR for rows
#define SR_ROW_PORT		PORTC
#define SR_ROW_DDR		DDRC

#define SR_ROW_SER		PC3
#define SR_ROW_RCLK		PC4
#define SR_ROW_SRCLK	PC5

// LED Matrix SR for columns
#define SR_COL_PORT		PORTB
#define SR_COL_DDR		DDRB

#define SR_COL_SER		PB0
#define SR_COL_RCLK		PB1
#define SR_COL_SRCLK	PB2

// SR for piece
#define SR_PIECE_PORT	PORTD
#define SR_PIECE_DDR	DDRD

#define SR_PIECE_SER	PD2
#define SR_PIECE_RCLK	PD3
#define SR_PIECE_SRCLK	PD4

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
