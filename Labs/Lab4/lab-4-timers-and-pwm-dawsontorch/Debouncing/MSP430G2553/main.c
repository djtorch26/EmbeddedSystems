#include <msp430.h> 


/**
 * Author: Dawson Tocarchick
 * Version 1.0 | October 2019
 * Button Based Delay Code for the G2553 board.
 *
 *Button Debouncing using a Timer
*/
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR &= 0x00;  //clears port directions
	P1OUT &= 0x00;  //clears output of port

//Led instantion
	P1DIR |= BIT0;   //P1.0 is an output
	P1OUT &= ~BIT0;  //LED 1.0 is off (to start

//button instantiation with interrupts enabled
	P1DIR &= ~BIT3;   //Sets 1.3 as an input
	P1IFG = 0x00;     //clears any interrupt flags
	P1IES |= BIT3;    //Interrupt enable on low to high
	P1IE |= BIT3;     //enable interrupt on 1.3



//Timer instantiation
	TA0CTL |= TASSEL_2 + MC_2; //select smclk, and continuous mode
	TA0CCR0 = 0x1388;         //Timer will count to this value about 5ms
	TA0CCTL0 |= CCIE;         //Enable interrupts with the compare 0
	TA0CTL |= TAIE;           //enable timer interrupts

__bis_SR_register(CPUOFF + GIE);

while(1);
}


//timer Interrupt Vector
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void){

        TA0CTL &= ~TAIFG;     //clear interrupt flags

        TA0CTL &= ~MC_3;       //sets clock to stop mode

    if(!(P1IN & BIT3)){
        P1OUT ^= BIT0;      //blink LED if button pressed
    }
}

//Button interrupt vector
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void){

    P1IFG &= ~BIT3;     //clears flag

    TA0R = 0;           //resets timer
    TA0CTL &= ~MC_3;    //~MC_3 --> 00, sets 00 in the mode select bits
    TA0CTL |= MC_2;     //Timer counts in continuous mode.
}

