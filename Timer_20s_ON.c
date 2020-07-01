#include <msp430.h> 

#define RED_LED     0x0001  // P1.0 is the Red LED
#define DEVELOPMENT 0x5A80  // stop the watchdog timer
#define ENABLE_PINS 0xFFFE // required to use inputs and outputs
#define ACLK        0x0100 // Timer_A Auxilliary Clock source
#define UP          0x0010 // Timer_A UP mode
#define TAIFG       0x0001 // Used to look at Timer A Interrupt FlaG

/**
 * main.c
 */
main()// 20,000,000 us / 25us = 800,000
{
    unsigned char intervals = 0;
	WDTCTL  = DEVELOPMENT;	// stop watchdog timer

	PM5CTL0 = ENABLE_PINS; // enable inputs and outputs

	TA0CCR0 = 50000;      // count from 0 to 50,000
	TA0CTL  = ACLK | UP;  // Use ACLK, for UP mode

	P1DIR   = RED_LED;    // set Red LED as an output
	P1OUT   = RED_LED;    // Turn red LED on
	
	while(1)
	{
	    if(TA0CTL & TAIFG) // If timer has counted to 50,000
	    {
	        intervals++;// update number of 50,000 counts
	        TA0CTL = TA0CTL & (~TAIFG); // count again

	        if (intervals == 16) // If counted 16 * 50,000 = 800,000
	        {
	            P1OUT = 0x00;   // Turn off red LED
	            while(2);       // and stay here forever
	        }
	    }
	}
}
