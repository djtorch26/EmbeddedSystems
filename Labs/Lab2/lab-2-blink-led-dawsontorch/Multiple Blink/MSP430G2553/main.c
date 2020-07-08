#include <msp430.h> 


/**
 * Author: Dawson Tocarchick
 * Version 1.0 | September 2019
 * Multiple Blink Code for the G2553 board.
 *
 * blinks 2 led's at different rates.
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	   P1DIR |= BIT0;                          // Clear P1.0 output latch for a defined power-on state
	    P1OUT |= BIT0;                          // Set P1.0 to output direction

	    P2DIR |= BIT1;                          //setting P2.1 output
	    P2OUT |= BIT1;                          //Sets Bit 1 to high from the P2DIR


	    while(1)
	    {


	        P1OUT ^= BIT0;                      // Toggle 1.0 LED
	        __delay_cycles(100000);
	        P1OUT ^= BIT0;                      //Toggle 1.0 LED again to double its frequency
	        __delay_cycles(100000);

	        P2OUT ^= BIT1;                      //Toggle 9.7 LED
	        __delay_cycles(1000000);



	    }


}
