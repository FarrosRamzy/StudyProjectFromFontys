# Basic STM32 LED Setup

I built this small exercise to understand the minimum register configuration required to use a GPIO output on the Nucleo-F303RE.

I enabled the GPIOA peripheral clock and configured PA5, the board's green LED pin, as a push-pull output with an appropriate output speed. The project focuses on peripheral setup rather than a larger runtime workflow, so it served as my starting point for reading the STM32 reference manual and manipulating registers directly.

## What I implemented

- GPIOA clock enable through the RCC register
- PA5 output-mode configuration
- Push-pull output type and output-speed setup
- STM32CubeIDE project and clock configuration

## Hardware and tools

- STM32 Nucleo-F303RE
- Onboard green LED on PA5
- STM32CubeIDE
- C and CMSIS register definitions

## Run

Open the project folder in STM32CubeIDE, build it, and flash it to a Nucleo-F303RE. The related assignment and register explanation are available in [the GPIO report](../../document/es_03_lab_01.pdf).
