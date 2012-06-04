/*
 * kelloggb_lab8_part3.c - May 4, 2012
 *
 * Name & E-mail: Benjamin Kellogg kelloggb@cs.ucr.edu
 * CS Login: kelloggb
 * Partner(s) Name & E-mail: Gabriel Limon glimo002@ucr.edu
 * Lab Section: 021
 * Assignment: Lab # 8 Exercise # 3
 * Exercise Description: Press key, display on LCD.
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
unsigned char *LCD_Data = &PORTB; // LCD 8-bit data bus
unsigned char *LCD_Ctrl = &PORTD; // LCD needs 2-bits for control, use port B
const unsigned char LCD_RS=2;     // LCD Reset pin is PD2
const unsigned char LCD_E=3;      // LCD Enable pin is PD3

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

// Returns '\0' if no key pressed, else returns char '1', '2', ... '9', 'A', ... 
// If multiple keys pressed, returns rightmost-bottommost one
// Keypad must be connected to port C
/* Keypad arrangement
        PC4 PC5 PC6 PC7   
    col  1   2   3   4   
   row 
PC0 1    1   2   3   A
PC1 2    4   5   6   B
PC2 3    7   8   9   C
PC3 4    *   0   #   D
*/
unsigned char GetKeypadKey() {
   unsigned char c='N';
   
   // Check keys in col 1
   PORTC = 0xFF; PORTC = SetBit(PORTC,4,0); // Set all col bits, then PC4 to 0
   
   if (GetBit(PINC,0)==0) { c = '1'; return(c); }
   if (GetBit(PINC,1)==0) { c = '4'; return(c); }
   if (GetBit(PINC,2)==0) { c = '7'; return(c); }
   if (GetBit(PINC,3)==0) { c = '*'; return(c); }
   
   // Check keys in col 2	
   PORTC = 0xFF; PORTC = SetBit(PORTC,5,0);
   if (GetBit(PINC,0)==0) { c = '2'; return(c); }
   if (GetBit(PINC,1)==0) { c = '5'; return(c); }
   if (GetBit(PINC,2)==0) { c = '8'; return(c); }
   if (GetBit(PINC,3)==0) { c = '0'; return(c); }
   
   // Check keys in col 3	
   PORTC = 0xFF; PORTC = SetBit(PORTC,6,0);
   if (GetBit(PINC,0)==0) { c = '3'; return(c); }
   if (GetBit(PINC,1)==0) { c = '6'; return(c); }
   if (GetBit(PINC,2)==0) { c = '9'; return(c); }
   if (GetBit(PINC,3)==0) { c = '#'; return(c); }
   
   // Check keys in col 4	
   PORTC = 0xFF; PORTC = SetBit(PORTC,7,0);
   if (GetBit(PINC,0)==0) { c = 'A'; return(c); }
   if (GetBit(PINC,1)==0) { c = 'B'; return(c); }
   if (GetBit(PINC,2)==0) { c = 'C'; return(c); }
   if (GetBit(PINC,3)==0) { c = 'D'; return(c); }

   return(c);
}

// SynchSM for testing the LCD interface -- waits for button press, fills LCD with repeated random num

unsigned char key;

enum LT_States { LT_s0, LT_WaitLcdRdy, LT_WaitButton, LT_FillAndDispString, 
LT_HoldGo1, LT_WaitBtnRelease } LT_State;

void LT_Tick() {
   static unsigned short j;
   static unsigned char  i, c;
   unsigned char okey;
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
            LT_State = LT_WaitButton;
         }
         break;
      case LT_WaitButton:
	  key = GetKeypadKey();
         if (key == 'N') {
            LT_State = LT_WaitButton;
         }
         else if (key != 'N' ) { // Button active low
            LT_State = LT_FillAndDispString;
         }
         break;
      case LT_FillAndDispString:
	     LT_State = LT_HoldGo1;        
         break;
	  case LT_HoldGo1:
	     LCD_go_g=0;
	     LT_State = LT_WaitBtnRelease;
		 break;
      case LT_WaitBtnRelease:
	  okey = key;
	  key = GetKeypadKey();
         if (key == okey) { // Wait for button release
            LT_State = LT_WaitBtnRelease;
         }
         else if (key != okey) {
            LT_State = LT_WaitLcdRdy;
         }
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
      case LT_WaitButton:
         break;
      case LT_FillAndDispString:
		 for (i=0; i<16; i++) { // Fill string with c
		    LCD_string_g[i] = key;
		 }
		 LCD_string_g[i] = '\0'; // End-of-string char
		 LCD_go_g = 1; // Display string
         break;
	  case LT_HoldGo1:
	     break;
      case LT_WaitBtnRelease:
         break;
      default: 
         break;
   } // State actions
}

int main() {
   DDRB  = 0xFF; // Set port B to output
   DDRD  = 0xFF; // Set port D to output
   DDRC  = 0xF0; PORTC = 0x0F;// Set port C to input/output
   DDRA  = 0x00; PORTA = 0xFF; // Set port A to input
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
