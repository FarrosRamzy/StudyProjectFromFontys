# Dual-Button External Interrupt Control

I built this project to control two LEDs without continuously polling both buttons in the main loop. PA8 and PA9 are connected to EXTI lines, while PB1 and PB2 are used as LED outputs.

On a button press and release, the interrupt handler records the rising and falling timestamps using a custom SysTick-based millisecond counter. A short press turns the matching LED on, while a long press turns it off. The main loop remains empty because the behavior is driven by interrupts and state transitions.

## What I implemented

- GPIO input and output configuration through registers
- SYSCFG and EXTI routing for PA8 and PA9
- NVIC interrupt enable and priority setup
- Rising/falling-edge switching inside the ISR
- Button-duration measurement
- Independent LED state machines for short and long presses

## Run

Open the project in STM32CubeIDE, build and flash it, then wire two buttons and two LEDs according to [the interrupt assignment report](../../document/es_03_lab_02.pdf).
