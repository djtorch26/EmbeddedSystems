#include <msp430.h> 


/**
 * Author: Dawson Tocarchick
 * Version 1.0 | October 2019
 *Software PWM Code for the G2553 board.
 *
*/
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR = 0x00;   //reset Directions on port 1
	P1OUT = 0x00;   //reset port 1 to all zeros

	P1DIR |= BIT0;  //set P1.0 as an output

	P1DIR |= BIT6; //set P1.6 as an output
    P1OUT &= ~BIT6; //At startup LED is Off

    P1DIR &= ~BIT3; //set P1.3 as an input
    P1REN |= BIT3; //enable pullup resistor
    P1OUT |= BIT3; //enable pullup resistor on 1.3
    P1IES |= BIT3; //enable interrupt rising edge
    P1IE |= BIT3; //enable interrupt on 1.3
    P1IFG &= ~BIT3; //clear interrupt flags

    TA0CTL = TASSEL_2 | MC_1; //timer A0 instantiation
    TA0CCR0 = 1000; //100% duty cycle
    TA0CCR1 = 500; //50% duty cycle

    TA0CCTL0 |= CCIE; //enable CCR0 reset interrupt
    TA0CCTL1 |= CCIE; //enable CCR0 interrupt
    TA0CTL |= TAIE; //enable Timer interrupts

    TA1CTL = TASSEL_2 | MC_2; //timer A1 instantiation
    TA1CCR0 = 64; //sets max time for reset flags
    TA1CCTL0 |= CCIE; //enable interrupts
    TA1CTL |= TAIE; //enable Timer interrupts

    __bis_SR_register(LPM0_bits + GIE); //enter LPM 0 and enable interrupts

   while(1);
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1 (void)
{
    P1IFG &= ~BIT3; //clear interrupt flag
    TA1R = 0; //reset timer
    TA1CTL = TASSEL_1 | MC_2; //Startup in continuous mode
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0 (void)
{
    TA1CTL &= ~TAIFG; //clear interrupt flag
    TA1CTL &= ~MC_3; //Stop clock for debouncing

    if(!(P1IN & BIT3) && (P1IES & BIT3)) //if button is pressed
    {
        P1IES &= ~BIT3; //flip interrupt edge
        P1OUT |= BIT6; //Turn LED 1.6 on

        if(TA0CCR1 <= 900) //if Duty Cycle is not @ 100%
        {
            TA0CCR1 += 100; //Increases Duty Cycle by 10%
            TA0CTL |= MC_1; //timer in up mode
        }
        else
        {
            TA0CCR1 = 0; //Duty cycle = 0
            TA0CTL &= ~MC_3; //Stops the timer
            P1OUT &= ~BIT0;//Turn LED 1.0 off
        }
    }

    if((P1IN & BIT3) && !(P1IES & BIT3)) // if button is released
        {
            P1IES |= BIT3; //flip interrupt edge
            P1OUT &= ~BIT6; //Turn LED 1.6 off
        }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0 (void)
{
    TA0CTL &= ~TAIFG; //clears interrupt flag
    P1OUT |= BIT0; //Turn LED 1.0 on
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1 (void)
{
    if(TA0IV == 0x02) //If interrupt comes from CCR1
    {
        P1OUT &= ~BIT0; //Turn LED 1.0 off
    }
}

