#include <msp430.h> 

#define RED_LED     0x0001 // P1.0 is the red LED
#define DEVELOPMENT 0x5A80 // Stop the watchdog timer
#define ENABLE_PINS 0xFFFE // Enable inputs and outputs
#define ACLK        0x0100 // Timer_A Auxiliary Clock source
#define UP          0x0010 // Timer_A UP mode
#define TAIFG       0x0001 // Used to look at Timer A Interrupt FlaG

//**************************************************************************
// Function Prototype
//**************************************************************************
void stop_watchdog_timer(void);        // These functions do not have an input
void enable_inputs_and_outputs(void); // or an output
void timer0_will_count_up_for_500ms(void);
void make_P10_red_LED_an_output(void);
void toggle_red_LED(void);
void clear_timer0_elapsed_flag(void);
//**************************************************************************
unsigned int timer0_500ms_elapsed(void); // Has an output, but no input
//**************************************************************************

/**
 * main.c
 */
main()
{
    stop_watchdog_timer();

    enable_inputs_and_outputs();


    timer0_will_count_up_for_500ms();

    make_P10_red_LED_an_output();

    while(1)
    {
        if(timer0_500ms_elapsed() )
        {
            toggle_red_LED();
            clear_timer0_elapsed_flag();
        }
    }// end while

}// end main

//*** Function Definitions ********************************************************
void stop_watchdog_timer(void)
{
    WDTCTL = DEVELOPMENT; // Disable watchdog timer for development
}
//*********************************************************************************
void enable_inputs_and_outputs(void)
{
    PM5CTL0 = ENABLE_PINS;  // Enables inputs and outputs
}
//*********************************************************************************
void timer0_will_count_up_for_500ms(void)
{
    TA0CCR0 = 20000;      // ACLK will increment every 25us
    TA0CTL  = UP | ACLK;  // 20,000 * 25 us = 0.5 seconds
}
//*********************************************************************************
void make_P10_red_LED_an_output(void)
{
    P1DIR = RED_LED;    // Makes pin P1.0 an output
}
//*********************************************************************************
void toggle_red_LED(void)
{
    P1OUT = P1OUT ^ RED_LED;    // Toggles the red LED on pin P1.0
}
//*********************************************************************************
void clear_timer0_elapsed_flag(void)
{
    TA0CTL = TA0CTL & (~TAIFG); // looks at the value of TAIFG as we defined
                                //  TAIFG = 0x0001 = 0000 0000 0000 0001

                                // Then, it bit-wise inverts the value
                                //  ~TAIFG = 0xFFFE = 1111 1111 1111 1110

                                // Then, it bit-wise ANDs the 0xFFFE value
                                // the contents of TA0CTL. This clears the TAIFG bit
                                // (bit 0 of TA0CTL) without modifying any of the other bits
}
//*********************************************************************************
unsigned int timer0_500ms_elapsed(void)
{                              // This takes the bit-wise logic AND of the value
    return TA0CTL & TAIFG;     // we defined for
                               //     TAIFG = 0x0001 = 0000 0000 0000 0001
                               // and the contents of the TA0CTL register

                               // The result will be returned as the output
                               // back to the main program

                               //  0x0000 If TAIFG is LO and the timer has not yet
                               //        counted up to TA0CCR0
                               //  0x0001 If TAIFG is HI and the timer has
                               //        counted up to TACCR0
}
//*********************************************************************************
