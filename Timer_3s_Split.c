#include <msp430.h> 

#define RED_LED     0x0001  // P1.0 is the red LED
#define DEVELOPMENT 0x5A80  // stop the watchdog timer
#define ENABLE_PINS 0xFFFE  // needed for inputs and outputs
#define ACLK        0x0100  // Timer_A Auxiliary Clock
#define UP          0x0010  // Timer_A UP mode
#define TAIFG       0x0001  // Used to look at Timer A Interrupt FlaG

/**
 * main.c
 */
main()
{
    unsigned char intervals = 0;  //count number of 40,000 counts

	WDTCTL  = DEVELOPMENT;	// stop watchdog timer
	PM5CTL0 = ENABLE_PINS;  // enable inputs and outputs

	TA0CCR0 = 40000;        // count from 0 to 40,000
	TA0CTL  = ACLK | UP;    // Use ACLK, for UP mode
	//In UP mode, timers count from 0 to the value you store in TA0CCR0

	P1DIR   = RED_LED;      // Set red LED as an output
	P1OUT   = RED_LED;      // Turn red LED on
	
	while(1)
	{
	    if(TA0CTL & TAIFG)              // returns true if  if the timer has reached the value you moved into the TA0CCR0 register
	    {                               // resulting in the TAIFG flag to go HI.

	        TA0CTL = TA0CTL & (~TAIFG); // count again
	        intervals++;                // update number of 40,000

	        if (P1OUT & RED_LED)       // If the red LED is on
	        {
	            if (intervals == 3)    //     Have 3 * 40,000 counts gone by?
	            {
	                P1OUT = 0x00;     //          If yes, Turn OFF LED
	                intervals = 0;    //          Clear number of 40,000 counts
	            }
	        }
	        else                      // Else, red LED is off
	        {
	            P1OUT = RED_LED;      //     Turn on the red LED
	            intervals = 0;        //     Clear number of 40,000 counts
	        }
	    }
	}// end while

}// end main
