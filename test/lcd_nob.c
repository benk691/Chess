/*
 * kelloggb_lab8_part2.c - May 4, 2012
 *
 * Name & E-mail: Benjamin Kellogg kelloggb@cs.ucr.edu
 * CS Login: kelloggb
 * Partner(s) Name & E-mail: Gabriel Limon glimo002@ucr.edu
 * Lab Section: 021
 * Assignment: Lab # 8 Exercise # 2
 * Exercise Description: Display "CS120B is Legend... wait for it DARY!" on LCD
 * 
 * I acknowledge all content contained herein is my own original work.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

/******** Bit-access functions ***************************************/
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
   return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}
/*--------END bit-access functions ----------------------------------*/


/******** Timer functions ********************************************/ 
volatile unsigned char TimerFlag=0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M=1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr=0; // Current internal count of 1ms ticks

void TimerOn() {
   // AVR timer/counter controller register TCCR0
   TCCR0 = 0x0B; // bit3bit6=10: CTC mode (clear timer on compare)
                 // bit2bit1bit0=011: prescaler /64
                 // 00001011: 0x0B
                 // SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
                 // Thus, TCNT0 register will count at 125,000 ticks/s

   // AVR output compare register OCR0.
   OCR0 = 125; // Timer interrupt will be generated when TCNT0==OCR0
               // We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
               // So when TCNT0 register equals 125,
               //    1 ms has passed. Thus, we compare to 125.
   // AVR timer interrupt mask register       
   TIMSK = 0x02; // bit1: OCIE0 -- enables compare match interrupt

   //Initialize avr counter
   TCNT0=0;

    _avr_timer_cntcurr = _avr_timer_M;
   // TimerISR will be called every _avr_timer_cntcurr milliseconds

    //Enable global interrupts
   SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
    TCCR0 = 0x00; // bit2bit1bit0=000: timer off
}

void TimerISR(){
    TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER0_COMP_vect)
{
   //CPU automatically calls this when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
   _avr_timer_cntcurr--;
   if (_avr_timer_cntcurr == 0) { // Count down to 0 rather than up to TOP (more efficient compare)
       TimerISR(); // Call the ISR that the user uses
       _avr_timer_cntcurr = _avr_timer_M;
   }
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}
/*--------END timer functions ---------------------------------------------------*/ 


/********* LCD interface synchSM *********************************************/

// Define LCD port assignments here so easier to change than if hardcoded below
unsigned char *LCD_Data = &PORTD; // LCD 8-bit data bus
unsigned char *LCD_Ctrl = &PORTB; // LCD needs 2-bits for control, use port B
const unsigned char LCD_RS=3;     // LCD Reset pin is PB3
const unsigned char LCD_E=4;      // LCD Enable pin is PB4

unsigned char LCD_rdy_g=0; // Set by LCD interface synchSM, ready to display new string
unsigned char LCD_go_g=0;  // Set by user synchSM wishing to display string in LCD_string_g
unsigned char LCD_string_g[17]; // Filled by user synchSM, 16 chars plus end-of-string char

void LCD_WriteCmdStart(unsigned char cmd) {
   *LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_RS, 0);  
   *LCD_Data = cmd; 
   *LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 1); 
}
void LCD_WriteCmdEnd() { 
   *LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 0); 
}
void LCD_WriteDataStart(unsigned char Data) {
   *LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_RS,1);  
   *LCD_Data = Data;  
   *LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 1);
}
void LCD_WriteDataEnd() {
   *LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 0);
}

enum LI_States { LI_Init1, LI_Init2, LI_Init3, LI_Init4, LI_Init5, LI_Init6, 
   LI_WaitDisplayString, LI_Clr, LI_PositionCursor, LI_DisplayChar, LI_WaitGo0 } LI_State;

void LI_Tick() {
   static unsigned char i;
   switch(LI_State) { // Transitions
      case -1:
         LI_State = LI_Init1;
         break;
      case LI_Init1:
         LI_State = LI_Init2;
         i=0;
         break;
      case LI_Init2:
         if (i<10) { // Wait 100 ms after power up
            LI_State = LI_Init2;
         }
         else {
            LI_State = LI_Init3;
         }
         break;
      case LI_Init3:
         if (1) {
            LI_State = LI_Init4;
            LCD_WriteCmdEnd();
         }
         break;
      case LI_Init4:
         if (1) {
            LI_State = LI_Init5;
            LCD_WriteCmdEnd();
         }
         break;
      case LI_Init5:
         if (1) {
            LI_State = LI_Init6;
            LCD_WriteCmdEnd();
         }
         break;
      case LI_Init6:
         if (1) {
            LI_State = LI_WaitDisplayString;
            LCD_WriteCmdEnd();
         }
         break;
      case LI_WaitDisplayString:
         if (!LCD_go_g) {
            LI_State = LI_WaitDisplayString;
         }
         else if (LCD_go_g) {
		    LCD_rdy_g = 0; 
            LI_State = LI_Clr;
         }
         break;
      case LI_Clr:
         if (1) {
            LI_State = LI_PositionCursor;
            LCD_WriteCmdEnd();
			i=0;
         }
         break;
      case LI_PositionCursor:
         if (1) {
            LI_State = LI_DisplayChar;
            LCD_WriteCmdEnd();
         }
         break;
      case LI_DisplayChar:
         if (i<16) {
            LI_State = LI_PositionCursor;
            LCD_WriteDataEnd();
			i++;
         }
         else {
            LI_State = LI_WaitGo0;
            LCD_WriteDataEnd();
         }
         break;
      case LI_WaitGo0:
         if (!LCD_go_g) {
            LI_State = LI_WaitDisplayString;
         }
         else if (LCD_go_g) {
            LI_State = LI_WaitGo0;
         }
         break;
      default:
         LI_State = LI_Init1;
      } // Transitions

   switch(LI_State) { // State actions
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
	     if ( i < 8 ) {
			 LCD_WriteCmdStart(0x80+i);
		 } 
		 else {
			 LCD_WriteCmdStart(0xB8+i);
		 }			 
         break;
      case LI_DisplayChar:
         LCD_WriteDataStart(LCD_string_g[i]);
         break;
      case LI_WaitGo0:
         break;
      default: 
         break;
   } // State actions
}
/*--------END LCD interface synchSM------------------------------------------------*/

 
// SynchSM for testing the LCD interface -- waits for button press, fills LCD with repeated random num

enum LT_States { LT_s0, LT_WaitLcdRdy, LT_FillAndDispString, 
LT_HoldGo1 } LT_State;

void LT_Tick() {
   static unsigned short j;
   static unsigned char  i, c;
   static unsigned long start = 0;
   static unsigned long end = 15;
   unsigned char msg[] = "CS120B is Legend... wait for it DARY!";
   unsigned char msgDisplay[16];
   unsigned long msgLen = 37;
   switch(LT_State) { // Transitions
      case -1:
         LT_State = LT_s0;
         break;
      case LT_s0:
         LT_State = LT_WaitLcdRdy;
         break;
      case LT_WaitLcdRdy:
         if (!LCD_rdy_g) {
            LT_State = LT_WaitLcdRdy;
         }
         else if (LCD_rdy_g) {
            LT_State = LT_FillAndDispString;
         }
         break;
      case LT_FillAndDispString:
	     LT_State = LT_HoldGo1;        
         break;
	  case LT_HoldGo1:
	     LCD_go_g=0;
	     LT_State = LT_WaitLcdRdy;
		 break;
      default:
         LT_State = LT_s0;
      } // Transitions

   switch(LT_State) { // State actions
      case LT_s0:
         LCD_go_g=0;
		   strcpy(LCD_string_g, "1234567890123456"); // Init, but never seen, shows use of strcpy though
         break;
      case LT_WaitLcdRdy:
         break;
      case LT_FillAndDispString:
	     j = 0;
	     if(start < end)
		 {
			 for(i = start; j < 16; i += 1)
			 {
				msgDisplay[j] = msg[i];
				j += 1;
			 }
		 }
		 else
		 {
			 for(i = end; i < msgLen; i += 1)
			 {
				msgDisplay[j] = msg[i]; 
				j += 1;
			 }
			 for(i = start; j < 16; i += 1)
			 {
				msgDisplay[j] = msg[i];
				j += 1; 
			 }
		 }
		 
		 for (i=0; i<16; i++) { // Fill string with c
		    LCD_string_g[i] = msgDisplay[i];
		 }
		 LCD_string_g[i] = '\0'; // End-of-string char
		 LCD_go_g = 1; // Display string
		 start = (start + 1) % msgLen;
		 end = (end + 1) % msgLen;	 
         break;
	  case LT_HoldGo1:
	     break;
      default: 
         break;
   } // State actions
}

int main() {
   DDRB  = 0xFF; // Set port B to output
   DDRD  = 0xFF; // Set port D to output
   DDRA  = 0x00; PORTA = 0xFF; 
   TimerSet(10);
   TimerOn();
   LI_State = -1;
   LT_State = -1;
   while(1) {
      LI_Tick();
      LT_Tick();
      while (!TimerFlag);
      TimerFlag = 0;
   }
}
