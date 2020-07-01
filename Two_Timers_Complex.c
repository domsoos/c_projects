#include <msp430.h> 

#define RED_LED      0x0001 // P1.0 is the red LED
#define GREEN_LED    0x0080 // P9.7 is the green LED
#define DEVELOPMENT  0x5A80 // Stop the watchdog timer
#define ENABLE_PINS  0xFFFE // Required to use inputs and outputs
#define ACLK         0x0100 // Timer_A ACLK source
#define UP           0x0010 // Timer_A UP mode
#define TAIFG        0x0001 // Used to look at Timer A Interrupt FlaG
#define PET_WATCHDOG 0x5A80 // WDT password and pet
/**
 * main.c
 */
main()
{
    unsigned char t0_count=0;
    unsigned char t1_count=0;

    PM5CTL0 = ENABLE_PINS;  // enable inputs and outputs

    TA0CCR0 = 400;         // count from 0 to 400 ~10ms
    TA0CTL  = ACLK | UP;    // Use ACLK, for UP mode

    TA1CCR0 = 40000;         // count from 0 to 40,000 ~1s
    TA1CTL  = ACLK | UP;    // Use ACLK, for UP mode

    P1DIR   = RED_LED;      // Set red LED as an output
    P9DIR   = GREEN_LED;    // Set green LED as an output

    while(1)
    {
        if(TA0CTL & TAIFG)  // If timer has counted to 5000
        {
            WDTCTL = PET_WATCHDOG;   // Pet the watchdog
            P1OUT  = P1OUT ^ RED_LED;// Then, toggle red P1.0 LED
            TA0CTL = TA0CTL & (~TAIFG); // count again
            t0_count++;            // increment 10ms counts

            if(t0_count == 10)    // If ~ 100ms has elapsed
            {
                t0_count = 0;       //      Reset 10ms counter
                P1OUT = P1OUT ^ RED_LED; // Toggle red LED
            }

        }// end timer0 if

        if(TA1CTL & TAIFG)           // If timer has counted to 5000
        {
            TA1CTL = TA1CTL & (~TAIFG); // count again
            t1_count++;                // increment 1s counts

            if(t1_count == 3)       // If  ~3s has elapsed
            {
                t1_count = 0;       //         Reset 1s counter
                P9OUT  = P9OUT ^ GREEN_LED;//  toggle red P1.0 LED
            }

        }// end timer1 if

    }// end while

}// end main
