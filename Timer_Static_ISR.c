#include <msp430.h> 

#define RED_LED         0x0001 // P1.0 is the red LED
#define STOP_WATCHDOG   0x5A80 // Stop the watchdog
#define ACLK            0x0100 // Timer_A Auxiliary Clock source
#define UP              0x0010 // Timer_A Up mode
#define ENABLE_PINS     0xFFFE // Required to use inputs and outputs

/**
 * main.c
 */
int main(void)
{
	WDTCTL   = STOP_WATCHDOG;	// stop watchdog timer

	PM5CTL0  = ENABLE_PINS;      // needed for input and output

	P1DIR    = RED_LED;          // Set red LED as an output

	TA0CCR0  = 20000;            // Set value of Timer
	TA0CTL   = ACLK + UP;        // Set ACLK, UP mode
	TA0CCTL0 = CCIE;             // Enable interrupt for Timer0

	_BIS_SR(GIE);                // Activate interrupt previously enabled
	
	while(1);
}
//************************************************************************
// Timer0 Interrupt Service Routine
//************************************************************************
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_ISR(void)
{
    static unsigned char x = 0; // used to count number of elapses

    x = x+1;                    // increment the elapse count

    if(x==15)
    {
        P1OUT = P1OUT ^ RED_LED; // Toggle red LED
        x = 0;
    }
}
