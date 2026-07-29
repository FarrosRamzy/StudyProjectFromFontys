# SysTick LED Pattern Controller

I combined the SysTick timing work with the earlier button and LED-pattern assignment. The program uses a custom SysTick delay instead of `HAL_Delay()` and controls a single LED together with a four-LED animation row.

PA8 toggles the single LED on PB1. PA9 switches between two animation styles on PB2-PB5. The project keeps the GPIO, timing, debounce, and sweep behavior at register level so I could practise using SysTick in a complete small application.

## What I implemented

- One-millisecond SysTick interrupt
- Custom countdown-based delay function
- Two button inputs on PA8 and PA9
- Five LED outputs on PB1-PB5
- Button debounce and press-release handling
- Two bidirectional LED sweep patterns

## Run

Import the project into STM32CubeIDE, build and flash it, then use [the SysTick report](../../document/es_03_lab_03.pdf) for the wiring and assignment context.
