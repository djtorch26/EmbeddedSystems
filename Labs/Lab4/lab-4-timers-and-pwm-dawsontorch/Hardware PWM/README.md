# Hardware PWM 

Hardware PWM is instead of using timer module as the frequency/duty cycle. We use The PWM functionality of the timer peripherals on the chip. A timer was also used to debounce the button. 

The functionality is to increase the PWM signal from 0% to 100% increasing by 10% each button press. 
The difference between both boards are the pinouts of the led's and buttons.