# Lab 3: Timers and Interrupts
During Lab 2, you probably noticed a few unexpected behaviors when trying to program a simple LED blink code. For starters, did you notice that it wasn't as straight forward to have the LED blink at a specific interval (it was not just a simple Clock/Blinking Rate to figure out the required delays). And when you had to deal with multiple LED's blinking at different rates, could you easily maintain the timing between the edges? What about if you wanted the LEDs to be on/off at rates (otherwise known as duty cycle)?

And what about that button? Do we really need to keep checking whether or not the button was pressed at the fastest rate possible? What about if we wanted to perform an action on just a falling or rising edge?

If you have not realized it, this lab is going to focus on how to remedy these problems using built in peripherals in the processors.

## Goals For the Lab
By the end of this lab, you should be able to:
* Configure the TIMER modules within the MSP430 processors to maintain more accurate timing.
* Begin to configure interrupts for GPIO.
* Utilize the built in clock dividers.
* Begin looking into Low Power Modes within the MSP430 Family

The main idea around this lab is the use of interrupts and showing that they can provide a new way of thinking about your system design. At the end of the day, you will be using the concepts developed in the previous lab and tying in the TIMER peripherals to perform what you were brute forcing in the last lab.

## Order of Exercises
Since GITHUB likes to alphabetize files, you need to perform the exercises in the following order:
1. Button Interrupt
2. TIMER A Blink
3. Button Based Delay
4. (Optional) Reaction Game

## Deliverables
By the end of the lab, you will need to provide at a minimum well documented main.c files for *EACH* of the development platforms used with accompanying README files which explain exactly how to implement your code. The reason I say minimum is that there is going to be some recommended further practice that is not mandatory, but highly recommended, especially if you are finishing this lab in only a few hours. So come Milestone time, I should see 4 folders in your repository with the following titles:
* Button Interrupt
* TIMER A Blink
* Button Based Delay
* (Optional) Reaction Game

each with the .c and README files for each board. The .c and README files should include the minimum amount of work as well as any extra work that you have done. Each processor should have its project saved in its own folder in each part of the assignment, however you only need one README per part of the assignment.

## Boards used
As with the previous lab, you will need to implement the exercises on the MSP430G2553 and the MSP430FR6989. 

### README Files
Since most of these projects will have just a simple main.c file, you do not need to generate 10 README files. Instead, unless you go for a more advanced implementation of the exercises, you just need 1 README per exercise folder. "But how do I make a README with all of the processors included?" Well now we are getting somewhere. You should talk about the general form of your code as it should be very similar for each processor, but you should highlight what the differences are between each processor. For example, do the clocks need to be initialized differently? As another step forward, you could take that information and somehow make it where your code would work on any of the processors without the need to change it between projects.

### Header Files
You may find yourself by the end of this lab not having generated any header files, which in this case, ignore this section. If you have generated more than just a main.c you most likely have yourself a .h file or two. Remember from the first lab that any header files or libraries that you generate need to have their own README.md which tell the user what dependencies there are, how to install them into their projects, etc.

## Documentation
Since you will most likely be using pre-made code to make most of your code, so what I am going to require you to do is comment each line of code and what it is doing. If you are using code from TI themselves, it will most likely have some of the comments there. But I want you to use your own words when writing these comments. Dive into the datasheets, look into the MSP430.h file to see what registers are being manipulated and tell me why you need to configure them.
