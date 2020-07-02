#include <msp430.h> 

#define STOP_WATCHDOG       0x5A80 // Stop watchdog timer
#define ACLK                0x0100 // Timer ACLK source
#define UP                  0x0010 // Timer UP mode
#define ENABLE_PINS         0xFFFE // Required to use inputs and outputs

/**
 * main.c
 */
main()
{
	WDTCTL   = STOP_WATCHDOG;	// stop watchdog timer

	PM5CTL0  = ENABLE_PINS;     // Required to use inputs and outputs

	P1DIR    = BIT0;            // Set pin for red LED as an output

	TA0CCR0  = 20000;           // Sets value of Timer0
	TA0CTL   = ACLK + UP;       // Set ACLK, UP mode
	TA0CCTL0 = CCIE;            // Enable interrupt for Timer0

	_BIS_SR(LPM0_bits | GIE);   // Activate interrupts previously enabled
	
	while(1);
}
//************************************************************************
// Timer0 Interrupt Service Routine
//************************************************************************
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_ISR (void)
{
    P1OUT = P1OUT ^ BIT0; // Toggle the red LED on P1.0
}
