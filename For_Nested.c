#include <msp430.h> 

#define DEVELOPMENT     0x5A80  // Stop the watchdog timer
main()
{
    unsigned long ones  = 0;    // Ones digit
    unsigned long tens  = 0;    // Tens digit
    unsigned long huns  = 0;    // Hundreds digit
    unsigned long thou  = 0;    // Thousands digit (1K)
    unsigned long tnth  = 0;    // Ten thousands digit (10K)
    unsigned long km    = 0;    // Total number of kilometers traveled


    WDTCTL = DEVELOPMENT;       // You will learn more about this in Section 7
                                // It is not strictly needed for a general C
                                // program, but it is necessary for the MSP430

    while(1)
    {
        for (tnth=0 ; tnth<10 ; tnth=tnth+1)// Outer loop counts 10K digit of km
        {
            for (thou=0 ; thou<10 ; thou=thou+1)// Outer loop counts 1K digit of km
            {
                for (huns=0 ; huns<10 ; huns=huns+1)// Outer loop counts hundredsns of km
                {
                    for (tens=0 ; tens<10 ; tens=tens+1) // Outer loop counts tens of km
                    {
                        for (ones=0 ; ones<10 ; ones=ones+1)// Inner loop counts km
                        {
                            km = 10000*tnth + 1000*thou + 100*huns + 10*tens + ones; // Total number of km
                        }// end ones digit loop

                    }// end tens digit loop

                }// end hundreds digit loop

            }// end thousands digit loop

        }//end ten thousands digit loop

        km = 0;

    }//end while(1)

}// end main()
