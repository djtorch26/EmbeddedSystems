#include <msp430.h> 


/**
 * Author: Dawson Tocarchick
 * Version 1.0 | September 2019
 * Button Based Delay Code for the G2553 board.
 *
 *
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1OUT &= 0x00;              //clear p1
	P1DIR &= 0x00;              //resets the port direction

	P1DIR |= BIT0;              //led is output
	P1OUT &= ~BIT0;             //bit0 is 0

	P1DIR &= ~BIT3;             //1.3 is an input
	P1REN |= BIT3;              //RES enabled on 1.3
	P1OUT |= BIT3;              //1.3 is on

	P1IE |= BIT3;                                       //P1.3 is set to interrupt
	P1IES |= BIT3;                                      //sets interrupt to falling edge of 1.3

	TA0CTL = TASSEL_2 + MC_1 + ID_3 + TACLR;            //SMCLK/8 "Up" mode

	TA0CCR0 = 10000;
	TA0CCTL0 = CCIE;                                     //enable clock interupt
	TA0CCTL0 &= 0x10;                                    //compare mode

	TA1CTL = TASSEL_2 + MC_0 + ID_3 + TACLR;            // SMCLK stop mode, divided by 8
	//TACCTL1= CM_1 + CCIS_0 + CAP + SCS + SCCI + CCIE;

	_BIS_SR(CPUOFF + GIE);
	while(1)
	{}
}

#pragma vector=TIMER0_A0_VECTOR //Timer interrupt vector
__interrupt void LED_BLINK(void){
    P1OUT ^= BIT0;                  //LED blink
}

#pragma vector=PORT1_VECTOR             //Button interrupt vector
__interrupt void button(void){
    if(!(P1IN & BIT3)){

     TA1CTL = TASSEL_2 + MC_2 + ID_3 +  +TACLR; //SMCLOCK continuous mode/8

     P1IES &= ~BIT3;            //Low to high transition on bit 3
    }
    else{
        TA1CTL = MC_0; //stop timer1, so it captures value

        TA0CCR0 = TA1R; //timer0 = timer1 val set after button release
        TA1R = 0; //reset capture timing value
        TA0CTL = TASSEL_2 + MC_1 + ID_3 + TACLR; // start timer 0 up mode

        P1IES |= BIT3; //high to low interrupt
    }
        P1IFG &= ~BIT3;     //reset flag
}







