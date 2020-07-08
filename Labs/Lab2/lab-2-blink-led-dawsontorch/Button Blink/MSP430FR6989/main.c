#include <msp430.h> 


/**
 * Author: Dawson Tocarchick
 * Version 1.0 | September 2019
 * Button Blink Code for the FR6989 board.
 *
 * LED on pin 1.0 will blink when button on port 1.1 is pressed
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	 PM5CTL0 &= ~LOCKLPM5;      //Disable GPIO power on default high_impedance

	 P1DIR = BIT0;              //sets P1.0 as an output
	 P1REN = BIT1;              //Enables internal resistor
	 P1OUT = BIT1;              //P1.1 is an input pin and sets as normally high

	 while(1)
	 {
	    if ((P1IN & BIT1)!= BIT1){       //if button is pressed run this code.
	     __delay_cycles(180000);
	     P1OUT ^= BIT0;                 //blink LED
	    }
	 }

}
