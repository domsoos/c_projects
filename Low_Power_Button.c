#include <msp430.h> 

#define STOP_WATCHDOG       0x5A80 // Stop the watchdog timer
#define ACLK                0x0100 // Timer ACLK source
#define UP                  0x0010 // Timer Up mode
#define ENABLE_PINS         0xFFFE // Required to use inputs and outputs
#define SLOW                0x00C0 // Slows down ACLK by factor of 8

/**
 * main.c
 */
int main(void)
{
	WDTCTL   = STOP_WATCHDOG;	    // Stop watchdog timer

	PM5CTL0  = ENABLE_PINS;         //  Required to use inputs and outputs

	P1DIR    = BIT0;                // Set pin for red LED as an output
	P1OUT    = 0x00;                // Make sure red LED is off to start

	P1OUT    = BIT1;                // P1.1 needs a pull-up resistor
	P1REN    = BIT1;                // P1.1 needs a pull-up resistor

	TA0CCR0  = 2000;                // 2K * 25us ~ 50ms ISR interval
	TA0CTL   = ACLK | UP;           // Set ACLK, UP mode
	TA0CCTL0 = CCIE;                // Enable interrupt for Timer0

	_BIS_SR(LPM0_bits | GIE);       // Activate interrupts previously enabled
	
	while(1);
}

//************************************************************************
// Timer0 Interrupt Service Routine
//************************************************************************
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_ISR(void)
{
    if(P1IN & BIT1)                 // If P1.1 button is not pushed
    {                               //
        P1OUT = P1OUT & ~BIT0;      //      BIT0 = 0000 0001 B
    }                               //     ~BIT0 = 1111 1110 B
                                    //      Bit-wise AND will clear P1OUT.0
                                    //      and not change P1.1 pull-up resistor

    else                            // Else, P1.1 button is pushed
    {                               //
        P1OUT = P1OUT | BIT0;       //      Turn on the red LED
    }
}
