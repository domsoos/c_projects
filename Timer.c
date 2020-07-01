#include <msp430.h> 

#define RED_LED     0x0001 //P1.0 is the red LED

#define DEVELOPMENT 0x5A80 // Stop the watchdog timer

#define ENABLE_PINS 0xFFFE // Required to use inputs and outputs

#define ACLK        0x0100 // Timer_A Auxiliary Clock source

#define UP          0x0010 // Timer_A UP mode

#define TAIFG       0x0001 // used to look at the Timer A Interrupt FlaG
/**
 * main.c
 */
main()
{

	WDTCTL  = DEVELOPMENT;	// stop watchdog timer
	PM5CTL0 = ENABLE_PINS;  // Enable inputs and outputs

	TA0CCR0 = 20000;        // (20000)(25us) = 0.5 seconds
	// 16 bit timer register.. highest num is 65,535

	TA0CTL  = ACLK | UP;    // Takes the logic OR of 0x0100 and 0x0010
	                        // and stores the result in TA0CTL
                            // When complete, TA0CTL = 0x0110

	P1DIR   = RED_LED;      // Set Red LED as an output
	
	while(1)                // If timer has counted to 20000
	{
	     if(TA0CTL & TAIFG) // Will be True if the TAIFG bit in TA0CTL
	     {                  // is HI

	         P1OUT  =  P1OUT ^ RED_LED;  //  Then, toggle red P1.0 LED

	         TA0CTL =  TA0CTL & (~TAIFG);//  Count again
	     }

	                        //  Count again
	}
}
