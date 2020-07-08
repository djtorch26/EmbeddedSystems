#include <msp430.h> 

/**
 * Author: Dawson Tocarchick
 * Version 1.0 | September 2019
 * TimerA Blink Code for the G2553 board.
 *
 *Blinks an LED based on timer interrupt
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1OUT &= 0x00;              //clears port 1
    P1DIR &= 0x00;              //clears directions for port 1

    P2OUT &= 0x00;
    P2DIR &= 0x00;

    CCTL0 = CCIE;               //CCR0 Interrupt enabled
    TA0CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK/ID_3(8), CountMode = up mode
    CCR0 = 12000;               //Sets CCR0

    P1DIR |= BIT0;      //Sets port 1.0 as outputs rest are inputs still
    P2DIR |= BIT1 + BIT5;      //sets P2 direction of pins 2.3, and 2.5

    TA1CCTL0 = CCIE;
    TA1CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK/ID_3(8), CountMode = up/down mode
    TA1CCR0 = 24000;                    //sets top value of timer 1 to set flags


    _BIS_SR(CPUOFF + GIE);
while(1)
    {}
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0 (void)
{
    P1OUT ^= BIT0;          //toggle p1.0 with timer A freq

}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void TIMER1 (void)
{
    P2OUT ^= BIT1 + BIT5;
}







