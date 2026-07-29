# External Interrupt Assignment

I rebuilt the earlier button-and-LED behavior using STM32 external interrupts instead of depending only on polling in the main loop.

The projects configure SYSCFG, EXTI lines 8 and 9, NVIC priorities, and a custom millisecond counter. I used both rising and falling edges to measure how long a button was held and then applied short- and long-press rules.

- [Dual-Button Interrupt Control](./source_code/interrupts_a_assignment/) controls two independent LEDs.
- [Interrupt-Driven LED Patterns](./source_code/interrupt_b_assignment/) controls one LED and switches between animated LED patterns.

The full setup and test results are available in [the interrupt report](./document/es_03_lab_02.pdf).
