# SysTick Polling Delay

I created this project to replace `HAL_Delay()` with a delay based directly on the Cortex-M SysTick registers.

SysTick is configured with the 16 MHz system clock and a one-millisecond reload interval. My `DelayMS()` function polls the timer's COUNTFLAG and counts the requested number of ticks. The program toggles an LED on PB1 and waits three seconds between changes.

## What I implemented

- SysTick clock-source and reload configuration
- A polling-based millisecond delay
- Direct PB1 GPIO configuration
- LED toggle through the output-data register

## Run

Open and flash the project with STM32CubeIDE. Connect an LED to PB1 and consult [the SysTick report](../../document/es_03_lab_03.pdf) for the original setup.
