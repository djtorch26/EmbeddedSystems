#include <msp430.h> 


/**
 * Author: Dawson Tocarchick
 * Version 1.0 | September 2019
 * Button Blink Code for the G2553 board.
 *
 * LED on pin 1.0 will blink when button on port 1.3 is pressed
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR = BIT0;              //sets P1.0 as an output
    P1REN = BIT3;              //Enables internal resistor
    P1OUT = BIT3;              //P1.3 is an input pin and sets as normally high

    while(1)
    {
       if ((P1IN & BIT3)!= BIT3){   //if button pressed run blink LED
        __delay_cycles(180000);     //delay between blinks
        P1OUT ^= BIT0;              //LED toggle on or off based off of the button
       }
    }


}
