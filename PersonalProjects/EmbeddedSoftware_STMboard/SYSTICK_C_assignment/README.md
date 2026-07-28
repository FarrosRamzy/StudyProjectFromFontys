# SysTick Button and LED Controller

I combined SysTick timing with button input and LED mode switching. The firmware reads a button, changes the output mode, and updates LEDs through interrupt-driven timing instead of `HAL_Delay`.

## My work

I configured the required STM32 peripherals, wrote the user logic in C, tested the behaviour on the Nucleo-F303RE board, and used the assignment to practise reading the reference manual and manipulating peripheral registers.
