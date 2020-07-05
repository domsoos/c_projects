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
    P1DIR   = BIT0;             // Set Red LED to output
    P9DIR   = BIT7;             // Set Green LED to output

    ADC_SETUP();                // sets up ADC peripheral

    ADC12IER0 = ADC12IE0;       // Enable Analog to Digital conversion
    _BIS_SR(GIE);               // Activate interrupts

    ADC12CTL0 = ADC12CTL0 | ADC12ENC; // Enable conversion
    ADC12CTL0 = ADC12CTL0 | ADC12SC;  // Start conversion

    while(1);

}// end main

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    #define ADC12_P84 0x0007    // Use input P8.4 for analog input
    #define ADC12_P92 0x000A    // use input P9.2 for analog input

    static unsigned char input = 84;// input = 84 if P8.4 sampled
                                    //       = 92 if P9.2 samples

    if(input == 84)             // If sample was from P8.4
    {
        if (ADC12MEM0 > 0x800)  //   If input > 1.65V (50%)
        {
            P1OUT = BIT0;       //      Turn red LED on
        }
        else                    //   Else input <= 1.65V
        {
            P1OUT = 0x00;       //      Turn red LED off
        }
        input = 92;

        ADC12CTL0 =  ADC12CTL0 & (~ADC12ENC); // Need to disable peripheral
        ADC12MCTL0 = ADC12_P92;               // to change to input P9.2
    }
    else                        // Else, sample was from P9.2
    {
        if(ADC12MEM0 > 0x800)   //      If input > 1.65V (50%)
        {
            P9OUT = BIT7;       //          Turn red LED on
        }
        else                    //      Else input <= 1.65
        {
            P9OUT = 0x00;       //           Turn red LED off
        }
        input = 84;             // Next sample from P8.4

        ADC12CTL0 = ADC12CTL0 & (~ADC12ENC);// Need to disable peripheral
        ADC12MCTL0 = ADC12_P84;             // to change to input P8.4
    }

    ADC12CTL0 = ADC12CTL0 | ADC12ENC;// Re-enable conversion
    ADC12CTL0 = ADC12CTL0 | ADC12SC; // Start next conversion
}
//************************************************************************
//* Configure Analog-to-Digital Converter peripheral**********************
//************************************************************************
void ADC_SETUP(void)
{
    #define ADC12_SHT_16        0x0200  // 16 clock cycles for sample and hold
    #define ADC12_ON            0x0010  // Used to turn ADC12 peripheral on
    #define ADC12_SHT_SRC_SEL   0x0200  // Selects source for sample and hold
    #define ADC12_12BIT         0x0020  // Select 12-bits of resolution

    #define ADC12_P84           0x0007  // Use input P8.4 for analog input
    #define ADC12_P85           0x0006  // Use input P8.5 for analog input
    #define ADC12_P86           0x0005  // Use input P8.6 for analog input
    #define ADC12_P87           0x0004  // Use input P8.7 for analog input

    #define ADC12_P90           0x0008  // Use input P9.0 for analog input
    #define ADC12_P91           0x0009  // Use input P9.1 for analog input
    #define ADC12_P92           0x000A  // Use input P9.2 for analog input
    #define ADC12_P93           0x000B  // Use input P9.3 for analog input
    #define ADC12_P95           0x000D  // Use input P9.5 for analog input
    #define ADC12_P96           0x000E  // Use input P9.6 for analog input

    ADC12CTL0  = ADC12_SHT_16 | ADC12_ON;
    ADC12CTL1  = ADC12_SHT_SRC_SEL;
    ADC12CTL2  = ADC12_12BIT;
    ADC12MCTL0 = ADC12_P84;

}















