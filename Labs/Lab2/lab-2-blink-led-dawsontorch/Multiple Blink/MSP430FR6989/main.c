
#include <msp430.h>


/**
 * Author: Dawson Tocarchick
 * Version 1.0 | September 2019
 * Multiple Blink Code for the FR6989 board.
 *
 * Two led's on P1.0 and P9.7 will blink at different rates
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop WDT

    P1DIR |= BIT0;                          // Clear P1.0 output latch for a defined power-on state
    P1OUT |= BIT0;                          // Set P1.0 to output direction

    P9DIR |= BIT7;                          //clearing P9.7 output
    P9OUT |= BIT7;                          //Sets Bit 7 to high from the P9DIR


    PM5CTL0 &= ~LOCKLPM5;                   //disables default high impedance mode.

    while(1)
    {


        P1OUT ^= BIT0;                      // Toggle 1.0 LED
        __delay_cycles(100000);
        P1OUT ^= BIT0;                      //Toggle 1.0 LED again to double its frequency
        __delay_cycles(100000);

        P9OUT ^= BIT7;                      //Toggle 9.7 LED
        __delay_cycles(1000000);



    }
}
