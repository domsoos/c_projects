#include <msp430.h> 

#define RED_LED     0x0001 // P1.0 is the red LED
#define GREEN_LED   0x0080 // P9.7 is the green LED
#define DEVELOPMENT 0x5A80 // Stop the watchdog timer
#define ENABLE_PINS 0xFFFE // Required to use inputs and outputs
#define ACLK        0x0100 // Timer_A ACLK source
#define UP          0x0010 // Timer_A UP mode
#define TAIFG       0x0001 // Used to look at Timer A Interrupt FlaG
/**
 * main.c
 */
main()
{
    WDTCTL  = DEVELOPMENT;  // stop watchdog timer
    PM5CTL0 = ENABLE_PINS;  // enable inputs and outputs

    TA0CCR0 = 33000;         // count from 0 to 33,000
    TA0CTL  = ACLK | UP;    // Use ACLK, for UP mode

    TA1CCR0 = 5000;         // count from 0 to 5,000
    TA1CTL  = ACLK | UP;    // Use ACLK, for UP mode

    P1DIR   = RED_LED;      // Set red LED as an output
    P9DIR   = GREEN_LED;    // Set green LED as an output

    while(1)
    {
        if(TA0CTL & TAIFG)  // If timer has counted to 5000
        {
            P1OUT  = P1OUT ^ RED_LED;// Then, toggle red P1.0 LED
            TA0CTL = TA0CTL & (~TAIFG); // count again
        }

        if(TA1CTL & TAIFG)  // If timer has counted to 5000
        {
            P9OUT  = P9OUT ^ GREEN_LED;// Then, toggle red P1.0 LED
            TA1CTL = TA1CTL & (~TAIFG); // count again
        }

    }// end while

}// end main
