# Button Based Delay

The goal of this lab was to control 2 timers at the same time, using TA0 and TA1. Essentially in this code, we had to allow interrupts on our main clock (toggle clock) which will blink an LED only when the clock counts up to CCR0, and resets to 0. Therefore, we can control the rate of blink by changing CCR0 on TA0, by using another timer (TA1). 

Accomplishing this task was fairly straightforward. When we hit a button we start TA1 from 0 and will count up to 0xFFFF, then when we let go of the button it will stop the timer, capturing the value in TA1R (total time button was pressed). Then inserting that value into TA0CCR0. Thus, giving the LED a different frequency to blink.