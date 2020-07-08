#include <msp430.h>

/**
 * Author: Dawson Tocarchick
 * Version 1.0 | October 2019
 *Software PWM using a Timer Code for the FR6989 board.
 *
*/
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; //stop watchdog timer


    PM5CTL0 &= ~LOCKLPM5; //disable the GPIO power-on default high-impedance mode


//P1.0 LED instantiation
    P1DIR |= BIT0; //set P1.0 as an output
    P1SEL0 |= BIT0; //selects P1.0 to use PWM

//P9.7 LED instantiation
    P9DIR |= BIT7; //set P9.7 as an output
    P9OUT &= ~BIT7; //Turn LED 9.7 off

//P1.1 button instatiation
    P1DIR &= ~BIT1; //set P1.1 as an input
    P1REN |= BIT1; //enable pullup resistor on 1.1
    P1OUT |= BIT1; //enable pullup resistor on 1.1

//P1.1 interrupt instantiation
    P1IES |= BIT1; //enable interrupt on rising edge
    P1IE |= BIT1; //enable interrupt
    P1IFG &= ~BIT1; //clear interrupt flags

//Timer1 setup
    TA1CTL = TASSEL__SMCLK | MC__CONTINUOUS; // timer A0 intantiation
    TA1CCR0 = 64; //Sets Timer reset 0 time for debouncing
    TA1CCTL0 |= CCIE; //enable interrupt

//Timer0 setup
    TA0CTL = TASSEL__SMCLK | MC__UP; // timer A0 instantiation
    TA0CCR0 = 1000; //100% duty cycle
    TA0CCR1 = 500; //50% duty cycle
    TA0CCTL1 |= OUTMOD_7; // resets output at CCR0, sets output at CCR1

    __bis_SR_register(LPM0_bits + GIE); //enter LPM 0 and enable interrupts

   while(1){}
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1 (void)
{
    P1IFG &= ~BIT1; //clear interrupt flag
    TA1R = 0; //reset timer
    TA1CTL = TASSEL__SMCLK | MC__CONTINUOUS; //start in continuous mode
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0 (void)
{
    TA1CTL &= ~TAIFG; //clear interrupt flag
    TA1CTL &= ~MC_3; //stop debouncingr

    if(!(P1IN & BIT1) && (P1IES & BIT1)) //if button is pressed
    {
        P1IES &= ~BIT1; //change button interrupt edge
        P9OUT |= BIT7; //turn on LED

        if(TA0CCR1 <= 900) //if the duty cycle is not 100%
        {
            TA0CCR1 += 100; //increase duty cycle by 10%
            TA0CTL |= MC_1; //up mode
            TA0CCTL1 |= OUTMOD_7; // change output mode
        }
        else
        {
            TA0CCR1 = 0; //set duty cycle back to 0
            TA0CTL &= ~MC_3; //stop timer
            TA0CCTL1 &= ~OUTMOD_7; //turn output off
        }
    }

    if((P1IN & BIT1) && !(P1IES & BIT1)) // if button is released
    {
        P1IES |= BIT1; //change button interrupt edge
        P9OUT &= ~BIT7; //turn off LED
    }
}
