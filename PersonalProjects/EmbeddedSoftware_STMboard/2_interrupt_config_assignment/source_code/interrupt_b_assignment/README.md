# Interrupt-Driven LED Pattern Controller

I used this project to improve the earlier polling-based LED pattern controller. The buttons are handled through EXTI interrupts, while the LED animation continues in the main loop using elapsed-time checks instead of long blocking delays.

The first button controls a single LED using short- and long-press behavior. The second button changes between two sweep patterns for a row of LEDs. SysTick provides the timing used both for button-duration measurement and non-blocking pattern updates.

## What I implemented

- EXTI handling for PA8 and PA9
- Short- and long-press detection
- A single LED on PB1
- Animated LED row on PB2-PB5
- Two selectable sweep modes
- Non-blocking animation timing using a custom `millis()` counter
- State enums for the single LED and sweep mode

## Run

Import the project into STM32CubeIDE, build and flash it, then follow [the interrupt report](../../document/es_03_lab_02.pdf) for the hardware setup and experiment background.
