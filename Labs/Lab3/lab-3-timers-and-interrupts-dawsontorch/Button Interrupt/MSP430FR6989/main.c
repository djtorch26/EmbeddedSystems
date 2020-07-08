#include <msp430.h>

static volatile int interruptFlag = 0;   //variable to change up or down


/**
 * Author: Dawson Tocarchick
 * Version 1.0 | September 2019
 * Button Interrupt Code for the FR6989 board.
 *
*/
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;       /* Disable the GPIO power-on default high-impedance mode
	                                to activate configured port settings*/

	TA0CCTL0 = CCIE;               //CCR0 Interrupt enabled
    TA0CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK/ID_3(8), CountMode = up mode
    TA0CCR0 = 12000;               //Sets CCR0

    P1OUT &= 0x00;              //clears port 1
    P1DIR &= 0x00;              //clears directions for port 1

    P1DIR |= BIT0;              //Sets pin 1.0 as output rest are inputs still
    P9DIR |= BIT7;              //sets pin 9.7 as output

    P1REN |= BIT1;              //Enable internal pull up/down resistor
    P1OUT |= BIT1;              //sets the resistor on 1.1 as a pullup resistor

    P1IE |= BIT1;               //interrupt enabled on p1.1
    P1IES |= BIT1;              //p1.1 high to low edge
    P1IFG &= ~BIT1;             //P1.1 Interrupt flag cleared.


    __enable_interrupt();       //enables interrupts
    _BIS_SR(LPM0 + GIE);      //Low power mode and general interrupt enable
    while(1)
    {}
}

	#pragma vector=TIMER0_A0_VECTOR
	__interrupt void TIMER_A (void)
	{
	        if(interruptFlag == 0){
	            P1OUT ^= BIT0;          //toggle p1.0 with timer A freq
	            P9OUT &= ~BIT7;          //Keep LED 9.7 off
	            }
	        if(interruptFlag == 1){
	            P9OUT ^= BIT7;          //Toggle 9.7 with timer A freq
	            P1OUT &= ~BIT0;          //1.0 is off when 2.5 is on
	            //P1IFG &= ~BIT3;
	            }

	}

	#pragma vector = PORT1_VECTOR           //button interrupt vector
	__interrupt void PORT1(void)
	{
	    interruptFlag ^= 1;     //toggles 1 or 0 for this variable
	    P1IFG &= ~BIT1;         //clear interrupt for 1.1
	}

