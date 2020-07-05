#include <msp430.h> 

#define ENABLE_PINS     0xFFFE // Enables inputs and outputs
void ADC_SETUP(void);          // Used to setup ADC12 peripheral

/**
 * main.c
 */
main()
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 = ENABLE_PINS;      // Enable inputs and outputs
    P1DIR   = BIT0;             // Set Red LEd to output

    ADC_SETUP();                // sets up ADC peripheral

    ADC12IER0 = ADC12IE0;       // Enable Analog to Digital conversion
    _BIS_SR(GIE);               // Activate interrupts

    ADC12CTL0 = ADC12CTL0 | ADC12ENC; // Enable conversion
    ADC12CTL0 = ADC12CTL0 | ADC12SC;  // Start conversion

    while(1);

}// end main

//************************************************************************
//* ADC12 Interrupt Service Routine***************************************
//************************************************************************
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    if(ADC12MEM0 > 0x800) // If input > 1.65V
    {
        P1OUT = BIT0;       //      Turn on red LED
    }
    else                    // Else input <= 1.65V
    {
        P1OUT = 0x00;       //      Turn off red LED
    }

    ADC12CTL0 = ADC12CTL0 | ADC12SC;  // Start the next conversion

}

