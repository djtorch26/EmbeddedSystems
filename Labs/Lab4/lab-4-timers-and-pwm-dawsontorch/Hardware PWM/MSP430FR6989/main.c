#include <msp430.h>

volatile int duty = 500; //Initial Duty Cycle Value


/**
 * Author: Dawson Tocarchick
 * Version 1.0 | October 2019
 * HardwarePWM Code for the FR6989 board.
 *
*/

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;        //holds watchdog timer


    PM5CTL0 &= ~LOCKLPM5;    // Disable the GPIO power-on default high-impedance mode to activate
                            // previously configured port settings

//LED instantiation p9.7
    P9DIR |= BIT7;  //Sets p9.7 as an output

//LED instantiation p1.0
    P1DIR |= BIT0;  //Sets P1.0 as an output
    P1SEL0 |= BIT0;  //Sets P1.0 to select PWM

//Button Instantiation p1.1
    P1DIR &= ~BIT1; //Sets P1.1 as an input
    P1OUT =  BIT1;  //Enables pullup resistor on p1.1
    P1REN |= BIT1;  //Enables pullup resistor on p1.1
    P1IE |= BIT1;   //Enables interrupt on 1.1
    P1IES |= BIT1;  //Enables interrupt on 1.1
    P1IFG &= ~BIT1; //Turns flag off at pin1.1

//Timer Instantiation
    TA0CCR0 = 1000;       //Duty Cycle @ 100%
    TA0CCTL1 = OUTMOD_7;  //Sets output mode for timer
    TA0CCR1 = duty;       //Duty Cycle @ 50%
    TA0CTL = TASSEL_2 + MC_1; //Timer Instantiation

     __bis_SR_register(LPM0_bits + GIE);  //Low power mode with Interrupts
    }

#pragma vector=PORT1_VECTOR       //interrupt Vector for when button is pressed
__interrupt void Button(void){
          P9OUT ^= BIT7;    //Button pressed, light up
 if (duty == 1000){        //if Duty Cycle is 100%
        duty = 0;          //Set Duty Cycle = 0
    } else {
        duty += 100;   // Increment Duty Cycle By 10%
    }
    TA0CCR1 = duty;          //Set Duty Cycle
    P1IFG = ~BIT1;           //Clears Flag
}
