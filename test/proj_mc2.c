/*
 * proj_mp2.c
 *
 * Created: 6/4/2012 7:38:40 AM
 *  Author: Embedded Systems Lab
 */ 

#include "../../include/LcdSM.h"
#include "../../include/KeypadSM.h"
#include "../../include/TimerDisplaySM.h"
#include "../../include/RecvMc2.h"
#include "../../include/SendMC2.h"

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

void synchWait()
{
	TimerSet(1000);
	TimerOn();
	
	while(!TimerFlag);
	TimerFlag = 0;
	
	TimerOff();
}

void init()
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;
	
	initUSART();
	synchWait();
}

int main(void)
{
	init();
	
    //Period for LCD Interface task.(10 ms)
	unsigned long int LCDI_period_calc = 10;
	//Period for Keypad task.(10 ms)
	unsigned long int Keypad_period_calc = 10;
	//Period for Timer Display task.(10 ms)
	unsigned long int TimerDisplay_period_calc = 10;
    //Period for Producer task. (50 ms)
	unsigned long int RP_period_calc = 5;
	//Period for Consumer task.(800 ms)
	unsigned long int RC_period_calc = 10;
	//Period for Producer task. (50 ms)
	unsigned long int SP_period_calc = 5;
	//Period for Consumer task.(100 ms)
	unsigned long int SC_period_calc = 10;

	//Calculating GCD
	unsigned long int tmpGCD = 1;
	tmpGCD = findGCD(LCDI_period_calc, Keypad_period_calc);
	tmpGCD = findGCD(tmpGCD, TimerDisplay_period_calc);
	tmpGCD = findGCD(tmpGCD, SP_period_calc);
	tmpGCD = findGCD(tmpGCD, SC_period_calc);
    tmpGCD = findGCD(tmpGCD, RC_period_calc);
    tmpGCD = findGCD(tmpGCD, RP_period_calc);
	
	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int LCDI_period = LCDI_period_calc/GCD;
	unsigned long int Keypad_period = Keypad_period_calc/GCD;
	unsigned long int TimerDisplay_period = TimerDisplay_period_calc/GCD;
    unsigned long int RP_period = RP_period_calc/GCD;
	unsigned long int RC_period = RC_period_calc/GCD;
	unsigned long int SP_period = SP_period_calc/GCD;
	unsigned long int SC_period = SC_period_calc/GCD;

	/*Declare an array of tasks and an integer containing the number of tasks in
	our system*/
	static task task1, task2, task3, task4, task5, task6, task7; /*Add or delete tasks as necessary*/
	task *tasks[] = { &task1, &task2, &task3, &task4, &task5, &task6, &task7 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	//LCD interface
	task1.state = -1;//Task initial state.
	task1.period = LCDI_period;//Task Period.
	task1.elapsedTime = LCDI_period;//Task current elasped time.
	task1.TickFct = &LCDI_SMTick;//Function pointer for the tick.
	
	//Keypad
	task2.state = -1;//Task initial state.
	task2.period = Keypad_period;//Task Period.
	task2.elapsedTime = Keypad_period;//Task current elasped time.
	task2.TickFct = &Keypad_Tick;//Function pointer for the tick.
	
	//Timer Display
	task3.state = Timer_Init_Wait;//Task initial state.
	task3.period = TimerDisplay_period;//Task Period.
	task3.elapsedTime = TimerDisplay_period;//Task current elasped time.
	task3.TickFct = &TimerDisplay_Tick;//Function pointer for the tick.
	
    //Recv Producer
	task4.state = RP_Init_Wait;//Task initial state.
	task4.period = RP_period;//Task Period.
	task4.elapsedTime = RP_period;//Task current elasped time.
	task4.TickFct = &RecvProducer_SMTick;//Function pointer for the tick.

	//Recv Consumer
	task5.state = RC_Init_Wait;//Task initial state.
	task5.period = RC_period;//Task Period.
	task5.elapsedTime = RC_period;//Task current elasped time.
	task5.TickFct = &RecvConsumer_SMTick;//Function pointer for the tick.

	//Send Producer
	task6.state = SP_Init;//Task initial state.
	task6.period = SP_period;//Task Period.
	task6.elapsedTime = SP_period;//Task current elasped time.
	task6.TickFct = &SendProducer_SMTick;//Function pointer for the tick.

	//Send Consumer
	task7.state = SC_Init_Wait;//Task initial state.
	task7.period = SC_period;//Task Period.
	task7.elapsedTime = SC_period;//Task current elasped time.
	task7.TickFct = &SendConsumer_SMTick;//Function pointer for the tick.

	//Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();

	unsigned short i; //Scheduler for-loop iterator
	while(1) 
	{
		//Scheduler code
		for ( i = 0; i < numTasks; i++ ) 
		{
			//Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period ) 
			{
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
