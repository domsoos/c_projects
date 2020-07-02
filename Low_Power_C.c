#include <msp430.h> 

#define STOP_WATCHDOG   0x5A80 // Stop the watchdog timer
#define ACLK            0x0100 // Timer ACLK source
#define UP              0x0010 // Timer UP mode
#define ENABLE_PINS     0xFFFE // Required to use input and outputs
#define SLOW            0x00C0 // Slow down ACLK by factor of 8

/**
 * main.c
 */
main()
{
    WDTCTL   = STOP_WATCHDOG;   // stop watchdog timer

    PM5CTL0  = ENABLE_PINS;     // Required to use inputs and outputs

    P1DIR    = BIT0;            // Set pin red LED as an output
    P1OUT    = 0x00;            // Make sure red LED is off to start

    P9DIR    = BIT7;            // Set pin for green LED as an output
    P9OUT    = 0x00;            // Make sure green LED is off to start

    TA0CCR0  = 40000;           // 40K * 200us ~ 8 second to ISR
    TA0CTL   = ACLK | UP | SLOW;// Set ACLK, UP mode
    TA0CCTL0 = CCIE;            // Enable interrupt for Timer0

    _BIS_SR(LPM0_bits | GIE);   // Enter Low Power Mode 0 and activate interrupts

    P9OUT    = BIT7;            // Turn on green LED after CPU comes
                                // out of low power mode
    while(1);
}
//************************************************************************
// Timer0 Interrupt Service Routine
//************************************************************************
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_ISR(void)
{
        _BIC_SR(LPM0_EXIT); // After 10 seconds, exit Low Power Mode 0
}
