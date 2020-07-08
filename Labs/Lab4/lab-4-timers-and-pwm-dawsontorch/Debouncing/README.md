# Software Debouncing

The code in this lab was meant to solve a problem that has been occuring during our other labs, we were wondering why sometimes a button press would cause 2-3 presses instead of the desired 1. Well this problem is caused by bouncing when a button is pressed, where a logic 0 can suddenly jump to a momentary 1 again, and your code would not know the difference between that and an actual button press.

Therefore we use code similar to the button interrupt, although the timer is not always running. The timer is started when the button is pressed, and stopped when it hits CCR0. Therefore, making a delay before the P1vector can be called again per each button press.