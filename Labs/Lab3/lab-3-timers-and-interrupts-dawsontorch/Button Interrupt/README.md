# Button Interrupt

In this part of the lab we were supposed to give a different behavior to our board when we pressed a button. Therefore, I used both a timer, and a button interrupt to accomplish this task. I used a variable called "interruptFlag". Which can only be a 1 or a 0. So inside of my button interrupt I control this variable, saying if the button is pressed change "interruptFlag" to a 1 or 0 depending on its prior state.

```c
#pragma vector = PORT1_VECTOR           //button interrupt vector
__interrupt void PORT1(void)
{
    interruptFlag ^= 1;     //toggles 1 or 0 for this variable
   // P1OUT ^= BIT6;          //toggle 1.6
    P1IFG &= ~BIT3;         //clear 1.3(button)
}
```

Next, We controlled our timer with that variable inside of the Timer interrupt vector using an if statement seen below,
```c
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
```
Essentially what this code says, is that if "interruptFlag" is a 0, blink the left LED keep the right LED off
if "interruptFlag" is a 1, Blink the right LED, keep the left LED off.