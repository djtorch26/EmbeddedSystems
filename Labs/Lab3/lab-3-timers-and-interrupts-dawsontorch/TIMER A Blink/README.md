# TIMER A BLINK

This lab was meant to teach us how to use the timer peripheral on our device.

In order to instantiate the clock we use
```c
TA0CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK/ID_3(8), CountMode = up mode
```

This will cause the clock to run on the sub-master clock system which is divided by 8 because of (ID_3). Finally, the clock is also set into up mode due to MC_1.

Now, since our timer is in up mode, we can use the Timer Reset Flag aka when timer reaches CCR0 and then resets, in order to blink our led.
So everytime the timer reaches CCR0, a value set by the coder, a flag is set, an LED is blinked, and the flag is cleared.

The same goes for Timer1 as well. Except we run that at a different frequency because our TA1CCR0 is a different value than TA0CCR0.
