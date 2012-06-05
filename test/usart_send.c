/*	send.c - 22-May-12 18:57:19
 *	Name & E-mail:  -
 *	CS Login:
 *	Partner(s) Name & E-mail:  -
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description:
 *
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

/******** Timer functions ********************************************/
// TimerISR() sets this to 1. C programmer should clear to 0.
volatile unsigned char TimerFlag=0;

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M=1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr=0; // Current internal count of 1ms ticks

volatile unsigned char pause_dequeue = 0;

void TimerOn()
{
	// AVR timer/counter controller register TCCR0
	TCCR0 = 0x0B;		// bit3bit6=10: CTC mode (clear timer on compare)
				// bit2bit1bit0=011: prescaler /64
				// 00001011: 0x0B
				// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
				// Thus, TCNT0 register will count at 125,000 ticks/s

	// AVR output compare register OCR0.
	OCR0 = 125;		// Timer interrupt will be generated when TCNT0==OCR0
				// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
				// So when TCNT0 register equals 125,
				// 1 ms has passed. Thus, we compare to 125.
				// AVR timer interrupt mask register

	TIMSK = 0x02; // bit1: OCIE0 -- enables compare match interrupt

	//Initialize avr counter
	TCNT0=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff()
{
	TCCR0 = 0x00; // bit2bit1bit0=000: timer off
}

void TimerISR()
{
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER0_COMP_vect)
{
	// CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
/*--------END timer functions ------------------------------------------------*/

/*--------Find GCD function --------------------------------------------------*/
unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a%b;
		if(c==0){return b;}
			a = b;
			b = c;
		}
	return 0;
}
/*--------End find GCD function ----------------------------------------------*/

/*--------Bit-access functions -----------------------------------------------*/
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}
/*--------END bit-access functions -------------------------------------------*/

/*--------Keypad function ----------------------------------------------------*/
// Returns '\0' if no key pressed, else returns char '1', '2', ... '9', 'A', ...
// If multiple keys pressed, returns leftmost-topmost one
// Keypad must be connected to port C
/* Keypad arrangement
       PC4 PC5 PC6 PC7
   col 1   2   3   4
row
PC0 1	1 | 2 | 3 | A
PC1 2	4 | 5 | 6 | B
PC2 3	7 | 8 | 9 | C
PC3 4	* | 0 | # | D
*/
unsigned char GetKeypadKey() {

	// Check keys in col 1
	PORTC = 0xEF;	// Set all col bits except PC4 to 1
	asm("nop");		// add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('1'); }
	if (GetBit(PINC,1)==0) { return('4'); }
	if (GetBit(PINC,2)==0) { return('7'); }
	if (GetBit(PINC,3)==0) { return('*'); }

	// Check keys in col 2
	PORTC = 0xDF;	// Set all col bits except PC5 to 1
	asm("nop");		// add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('2'); }
	if (GetBit(PINC,1)==0) { return('5'); }
	if (GetBit(PINC,2)==0) { return('8'); }
	if (GetBit(PINC,3)==0) { return('0'); }

	// Check keys in col 3
	PORTC = 0xBF;	// Set all col bits except PC6 to 1
	asm("nop");		// add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('3'); }
	if (GetBit(PINC,1)==0) { return('6'); }
	if (GetBit(PINC,2)==0) { return('9'); }
	if (GetBit(PINC,3)==0) { return('#'); }
	
	// Check keys in col 4	
	PORTC = 0x7F;	// Set all col bits except PC7 to 1
	asm("nop");		// add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('A'); }
	if (GetBit(PINC,1)==0) { return('B'); }
	if (GetBit(PINC,2)==0) { return('C'); }
	if (GetBit(PINC,3)==0) { return('D'); }

	return('\0'); // returns default NULL
}
/*--------END Keypad function ------------------------------------------------*/

/*--------Data structures-----------------------------------------------------*/
//Circular Queue
//Variables to implement our circular queue.
#define MAX_QUEUE_SIZE 32
unsigned char queue[MAX_QUEUE_SIZE]; //Queue of characters to output.
unsigned char queue_front = 0; //Queue front index.
unsigned char queue_back = MAX_QUEUE_SIZE-1; //Queue back index.
unsigned char queue_num_objects = 0; //Number of objects in queue.

//Functionality - Push a character onto back of queue
//Parameter: takes in a single unsigned char.
//Returns: 1 if full else 0.
unsigned char push_queue(unsigned char c) {
	//If queue is not full.
	//Increment back counter, modulate according to the max queue size,
	// and increase number of objects.*/
	//Put data into correct location.
	//Return not full.
	//Else Return queue is full.
	if(queue_num_objects<MAX_QUEUE_SIZE) {
		queue_back++;
		queue_back%=MAX_QUEUE_SIZE;
		queue_num_objects++;
		queue[queue_back] = c;
		return 0;
	}
	return 1;
}

//Functionality - Pop first character from top of queue.
//Parameter: None
//Returns: unsigned char from queue else null character.
unsigned char pop_queue() {
	//If queue is not empty.
	//Retrieve data in correct location.
	//Clear location with null character.
	//Increment front counter and modulate according to the max queue size.
	//Return data.
	//Else return null character to indicate empty.
	if(queue_num_objects>0){
		unsigned char tmp = queue[queue_front];
		queue[queue_front] = '\0';
		queue_front++;
		queue_front%=MAX_QUEUE_SIZE;
		queue_num_objects--;
		return tmp;
	}
	return '\0';
}

//Stack
//Variables to implement our stack.
#define MAX_STACK_SIZE 32
unsigned char stack[MAX_STACK_SIZE]; //Stack of characters to output.
unsigned char stack_front = 0; //Stack front index.
unsigned char stack_num_objects = 0; //Number of objects in queue.

//Functionality - Push a character onto front of stack
//Parameter: takes in a single unsigned char.
//Returns: 1 if full else 0.
unsigned char stack_queue(unsigned char c) {
	//If stack is not full.
	if(stack_num_objects<MAX_STACK_SIZE)
	{
stack[stack_front]=c;
stack_num_objects++;
		stack_front++;
		return 0;
	}
	return 1;
}

//Functionality - Pop first character from top of stack.
//Parameter: None
//Returns: unsigned char from stack else null character.
unsigned char pop_stack() {
	if(stack_num_objects>0)
	{
		stack_num_objects--;
		stack_front--;
		return stack[stack_front];
	}
	return '\0';
}
/*--------END Data structures-------------------------------------------------*/

/*--------UART functions -----------------------------------------------------*/
#define F_CPU 8000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALE (((F_CPU / (BAUD_RATE * 16UL))) - 1)

void initUSART(void)
{
	// Turn on the reception circuitry
	// Use 8-bit character sizes - URSEL bit set to select the UCRSC register
	UCSRB |= ((1 << RXEN) | (1 << TXEN));
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	/* Load lower 8-bits of the baud rate value into the low byte of the
		UBRR register	*/
	UBRRL = BAUD_PRESCALE;
	/* Load upper 8-bits of the baud rate value into the high byte of the
		UBRR register */
	UBRRH = (BAUD_PRESCALE >> 8);
}

void USART_Flush(void)
{
	unsigned char dummy;
	while ( UCSRA & (1<<RXC) ) dummy = UDR;
	return;
}

unsigned char USART_Received( void )
{
	// Wait for data to be received
	while ( !(UCSRA & (1<<RXC)) );
	// Get and return received data from buffer
	return UDR;
}

void USART_Send(char sendMe)
{
	while( !(UCSRA & (1 << UDRE)) );
	UDR = sendMe;
	return;
}
/*--------END UART functions -------------------------------------------------*/

/*--------Task scheduler data structure---------------------------------------*/
//Struct for Tasks represent a running process in our simple real-time operating system.
typedef struct _task {
	/*Tasks should have members that include: state, period,
		a measurement of elapsed time, and a function pointer.*/
	signed char state; //Task's current state
	unsigned long int period; //Task period
	unsigned long int elapsedTime; //Time elapsed since last task tick
	int (*TickFct)(int); //Task tick function
} task;

/*--------End Task scheduler data structure-----------------------------------*/

/*--------User defined FSMs---------------------------------------------------*/

/*Enumeration of states.*/
enum Producer_States { P_Init_Wait, P_Button_Press };

int Producer_SMTick(int state) {
	unsigned char c = GetKeypadKey();
	/*State machine transitions*/
	switch (state) {
	case P_Init_Wait: /* Init */
		if ( '\0' == c ) {
			state = P_Init_Wait;
		}
		else if (1) {
			if ( '#' == c ) { pause_dequeue = !pause_dequeue; }
			else { push_queue(c); }
			state = P_Button_Press;
		}
		break;

	case P_Button_Press:
		if ( '\0' != c ) {
			state = P_Button_Press;
		}
		else if (1) {
			state = P_Init_Wait;
		}
		break;

	default:
		state = P_Init_Wait;
		break;
	}

	/*State machine actions*/
	switch(state) {
	case P_Init_Wait: /* Init */
		break;

	case P_Button_Press:
		break;

	default:
		break;
	}
	return state;
}

/*Enumeration of states.*/
enum Consumer_States { C_Init_Wait, C_dequeue_tx };

int Consumer_SMTick(int state) {
	/*State machine transitions*/
	switch (state) {
	case C_Init_Wait: /* Init */
		if ( !queue_num_objects || pause_dequeue || !(UCSRA & (1 << UDRE)) ) {
			state = C_Init_Wait;
		}
		else if (1) {
			state = C_dequeue_tx;
			UDR = pop_queue();
		}
		break;

	case C_dequeue_tx:
		if ( !(UCSRA & (1 << TXC)) ) {
			state = C_dequeue_tx;
		}
		else if (1) {
			state = C_Init_Wait;
		}
		break;

	default:
		state = C_Init_Wait;
		break;
	}

	/*State machine actions*/
	switch(state) {
	case C_Init_Wait: /* Init */
		break;

	case C_dequeue_tx:
		break;

	default:
		break;
	}
PORTB = state;
	return state;
}

/*Add more state machines if necessary.*/


/*--------END User defined FSMs-----------------------------------------------*/

//Implement scheduler code from PES.
int main()
{
//Set Data Direction Registers
// Buttons PORTA[0-7], set AVR PORTA to pull down logic
DDRA = 0xFF; PORTA = 0x00;
/* LEDs (PORTB[0-2] & PORTB[5-7]) and LCD Control Signals(PORTB[3-4]),
		 set AVR PORTB to pull up logic also Note: AVR Programmer(PINB[5-7]) */
DDRB = 0xFF; PORTB = 0x00;
//Keypad(PINC[0-3] and PORTC[4-7]). set to pull up/down logic
DDRC = 0xF0; PORTC = 0x0F;
DDRD = 0xFF; PORTD = 0x00; //LCD Data Signals (PIND[0-7])

// Initialize USART
initUSART();

//Period for LCD Interface task.(10 ms)
//Period for Producer task. (50 ms)
unsigned long int P_period_calc = 50;
//Period for Consumer task.(1000 ms)
unsigned long int C_period_calc = 100;

//Calculating GCD
unsigned long int tmpGCD = 1;
tmpGCD = findGCD(P_period_calc, C_period_calc);

//Greatest common divisor for all tasks or smallest time unit for tasks.
unsigned long int GCD = tmpGCD;

//Recalculate GCD periods for scheduler
unsigned long int P_period = P_period_calc/GCD;
unsigned long int C_period = C_period_calc/GCD;

/*Declare an array of tasks and an integer containing the number of tasks in
our system*/
static task task1, task2; /*Add or delete tasks as necessary*/
task *tasks[] = { &task1, &task2 };
const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

//LCD interface
//Producer
task1.state = P_Init_Wait;//Task initial state.
task1.period = P_period;//Task Period.
task1.elapsedTime = P_period;//Task current elasped time.
task1.TickFct = &Producer_SMTick;//Function pointer for the tick.

//Consumer
task2.state = C_Init_Wait;//Task initial state.
task2.period = C_period;//Task Period.
task2.elapsedTime = C_period;//Task current elasped time.
task2.TickFct = &Consumer_SMTick;//Function pointer for the tick.

//Set the timer and turn it on
TimerSet(GCD);
TimerOn();

unsigned short i; //Scheduler for-loop iterator
while(1) {
		//Scheduler code
		for ( i = 0; i < numTasks; i++ ) {
			//Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				//Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				//Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
	/*Error: Program should not exit!*/
	return 0;
}