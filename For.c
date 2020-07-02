#include <msp430.h> 

#define RED_ON          0x0001 // Enable and turn on red led
#define RED_OFF         0x0000 // Turn off red LED
#define DEVELOPMENT     0x5A80 // Stop the watchdog timer
#define ENABLE_IO       0xFFFE //Used to ensure outputs are ready
/**
 * main.c
 */
main()
{
	WDTCTL  = DEVELOPMENT;      // stop the watchdog timer

	PM5CTL0 = ENABLE_IO;        // enable to turn on LED
	P1DIR   = RED_ON;           //Red LED pin will be an output
	P1OUT   = RED_OFF;          // start with the led off

	long x, z;

	for(x=0 ; x<30000 ; x=x+1)
	{
	    P1OUT = P1OUT ^ RED_ON;// Toggle red LED when x<30000

	    for(z=0 ; z<3000 ; z=z+1)
	    {
	        P1OUT = RED_OFF;
	    }
	}

	P1OUT = RED_OFF;            //Ensures LED is off

	while(1);
	
}
