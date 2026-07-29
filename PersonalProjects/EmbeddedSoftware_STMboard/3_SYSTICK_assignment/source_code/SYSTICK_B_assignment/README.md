# SysTick Interrupt LED Blink

I extended the SysTick exercise by enabling its interrupt instead of polling the COUNTFLAG in the main loop.

The interrupt handler increments a counter and toggles the LED on PB1 when the configured interval is reached. The main loop does not need to manage the timing, which helped me understand how periodic interrupt-driven tasks can run independently from normal application code.

## What I implemented

- SysTick interrupt configuration
- NVIC priority setup
- Periodic counter logic in `SysTick_Handler()`
- Direct PB1 LED control
- An interrupt-driven program with an otherwise empty main loop

## Run

Build and flash the project in STM32CubeIDE. The timer calculations and experiment are explained in [the SysTick assignment report](../../document/es_03_lab_03.pdf).
