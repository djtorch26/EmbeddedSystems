#include <msp430.h> 


/**
 * Author: Dawson Tocarchick
 * Version 1.0 | October 2019
 * Button Debouncing using a Timer Code for the FR6989 board.
 *
 *
*/
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       /* Disable the GPIO power-on default high-impedance mode
                                    to activate configured port settings*/

    P1DIR &= 0x00;  //clears port directions
    P1OUT &= 0x00;  //clears output of port

//Led instantion
    P1DIR |= BIT0;   //P1.0 is an output
    P1OUT &= ~BIT0;  //LED 1.0 is off (to start)

//button instantiation with interrupts enabled
    P1DIR &= ~BIT1;   //Sets 1.1 as an input
    P1REN |= BIT1;    //enables pullup resistor
    P1OUT |= BIT1;    //Enables Button

    P1IFG = 0x00;     //clears any interrupt flags
    P1IES |= BIT1;    //Interrupt enable on low to high
    P1IE |= BIT1;     //enable interrupt on 1.1



//Timer instantiation
    TA0CTL |= TASSEL_2 + MC_2; //select smclk, and continuous mode
    TA0CCR0 = 0x1388;         //Timer will count to this value about 5ms
    TA0CCTL0 |= CCIE;         //Enable interrupts with the compare 0
    TA0CTL |= TAIE;           //enable timer interrupts

    __enable_interrupt();       //enables interrupts
    _BIS_SR(LPM0 + GIE);      //Low power mode and general interrupt enable

while(1);
}


//timer Interrupt Vector
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void){

        TA0CTL &= ~TAIFG;     //clear interrupt flags

        TA0CTL &= ~MC_3;       //sets clock to stop mode

    if(!(P1IN & BIT1)){
        P1OUT ^= BIT0;      //blink LED if button pressed
    }
}

//Button interrupt vector
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void){

    P1IFG &= ~BIT1;     //clears flag

    TA0R = 0;           //resets timer
    TA0CTL &= ~MC_3;    //~MC_3 --> 00, sets 00 in the mode select bits
    TA0CTL |= MC_2;     //Timer counts in continuous mode.
}

