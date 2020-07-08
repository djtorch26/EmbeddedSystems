#include <msp430.h> 
#include <stdbool.h>

int interruptFlag = 0;   //variable to change up or down


/**
 * Author: Dawson Tocarchick
 * Version 1.0 | September 2019
 * Button Interrupt Code for the G2553 board.
 *
 *
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	CCTL0 = CCIE;               //CCR0 Interrupt enabled
	TACTL = TASSEL_2 + MC_1 + ID_3; //SMCLK/ID_3(8), CountMode = up mode

	CCR0 = 120000;               //Sets CCR0

	P1OUT &= 0x00;              //clears port 1
	P1DIR &= 0x00;              //clears directions for port 1

	P1DIR |= BIT0;              //Sets port 1.0 & 1.6 as outputs rest are inputs still

	P2DIR |= BIT5;

	P1REN |= BIT3;              //Enable internal pull up/down resistor
	P1OUT |= BIT3;              //sets the resistor on 1.3 as a pullup resistor

	P1IE |= BIT3;               //interrupt enabled on p1.3
	P1IES |= BIT3;              //p1.3 high to low edge
	P1IFG &= ~BIT3;             //P1.3 Interrupt flag cleared.

_BIS_SR(CPUOFF + GIE);
while(1)
	{}
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER_A (void)
{
    if(interruptFlag == 0){
    P1OUT ^= BIT0;          //toggle p1.0 with timer A freq
    P2OUT = ~BIT5;          //Turn off Blue LED (not Blinking when 1.0 is)
    }
    if(interruptFlag == 1){
    P2OUT ^= BIT5;          //Toggle 2.5 with timer A freq
    P1OUT = ~BIT0;          //1.0 is off when 2.5 is on
    //P1IFG &= ~BIT3;
    }

}

#pragma vector = PORT1_VECTOR           //button interrupt vector
__interrupt void PORT1(void)
{
    interruptFlag ^= 1;     //toggles 1 or 0 for this variable
   // P1OUT ^= BIT6;          //toggle 1.6
    P1IFG &= ~BIT3;         //clear 1.3(button)
}







