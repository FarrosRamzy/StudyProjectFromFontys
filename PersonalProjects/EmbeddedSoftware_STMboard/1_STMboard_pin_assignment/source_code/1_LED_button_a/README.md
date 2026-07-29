# Button-Controlled LED

I made this project to connect a physical input to an output using direct STM32 GPIO register access. Pressing the button on PA8 toggles an LED connected to PB1.

I separated the GPIO and LED-button logic into `my_led_button.c` and `my_led_button.h`. The program enables the GPIO clocks, configures PA8 as a pull-down input, configures PB1 as a push-pull output, debounces the button, and waits for release before accepting another press.

## What I implemented

- Direct RCC and GPIO register configuration
- PA8 button input with pull-down behavior
- PB1 LED output
- Button debouncing and press-release handling
- Reusable functions for reading, setting, and toggling pins

## Hardware

- STM32 Nucleo-F303RE
- One push button
- One LED and current-limiting resistor
- Breadboard and jumper wires

## Run

Open this folder as an STM32CubeIDE project, build it, flash the board, and connect the button and LED according to [the assignment report](../../document/es_03_lab_01.pdf).
