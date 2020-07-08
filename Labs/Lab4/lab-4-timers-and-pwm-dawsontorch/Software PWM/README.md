# Softwar PWM

This lab was meant to introduce us to the application of pulse width modulation on an LED. In doing so, we see that each time we press the button, the brightness increases, until 10 button presses, it goes to 0 (off).

This is controlled by the Timer1_A0_Vector in which it has an if statement for when the button is pressed it will increase the duty cycle by 100 (10%) until it reaches above 900 then it will reset the brightness and bring the duty cycle back to 0. Then this process will repeat.

