

#include <msp430.h>

/**
 * Author: Dawson Tocarchick
 * Version 1.0 | September 2019
 * Button Based Delay Code for the FR6989 board.
 *
 *Blinks an LED based on timer interrupt
*/
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       /* Disable the GPIO power-on default high-impedance mode
                                to activate configured port settings*/

    P1OUT &= 0x00;              //clears port 1
    P1DIR &= 0x00;              //clears directions for port 1

    P9OUT &= 0x00;              //clears port 9
    P9DIR &= 0x00;              //clears directions for port 9

    TA0CCTL0 = CCIE;               //CCR0 Interrupt enabled
    TA0CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK/ID_3(8), CountMode = up mode
    TA0CCR0 = 12000;               //Sets CCR0

    P1DIR |= BIT0;              //Sets port 1.0 as outputs rest are inputs still
    P1OUT |= ~BIT0;             //Pin 1.0 is instantiated low
    P9DIR |= BIT7;              //sets P9 direction of pins 9.7
    P9OUT |= ~BIT7;             //Pin 9.7 is instantiated low

    TA1CCTL0 = CCIE;
    TA1CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK/ID_3(8), CountMode = up/down mode
    TA1CCR0 = 24000;                    //sets top value of timer 1 to set flags

    __enable_interrupt();
    _BIS_SR(LPM0 + GIE);      //Low power mode and general interrupt enable
while(1)
    {}
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0 (void)
{
    P1OUT ^= BIT0;          //toggle p1.0 with timer0 reset flag

}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void TIMER1 (void)
{
    P9OUT ^= BIT7;       //Toggle p9.7 with Timer1 reset flag
}

