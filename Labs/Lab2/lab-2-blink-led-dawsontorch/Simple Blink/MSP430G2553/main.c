#include <msp430.h> 


/**
 * Author: Dawson Tocarchick
 * Version 1.0 | September 2019
 * Simple Blink Code for the G2553 board.
 *
 * LED on pin 1.0 will blink repeatedly.
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

           P1DIR |= BIT0;                          // Clear P1.0 output latch for a defined power-on state
            P1OUT |= BIT0;                          // Set P1.0 to output direction


            while(1)
            {
                P1OUT ^= BIT0;                      // Toggle 1.0 LED
                __delay_cycles(100000);
            }
}
