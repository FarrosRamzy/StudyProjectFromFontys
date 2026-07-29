# Button and LED Pattern Controller

I extended the first GPIO exercise into a small interactive LED controller. One button toggles a single LED, while a second button changes the operating mode of a four-LED row.

The row supports two sweep patterns: a single moving light and a progressive fill-and-clear animation. I implemented the GPIO setup and pattern logic through register access and kept the reusable behavior in a separate `my_led_button` module.

## What I implemented

- Two button inputs on PA8 and PA9
- A single LED output on PB1
- A four-LED pattern row on PB2-PB5
- Debounced button handling
- Off, sweep-A, and sweep-B operating modes
- Forward and reverse pattern state tracking

## What I learned

This version showed me the limitation of blocking delays: pressing a button can temporarily pause the LED animation. That observation became the motivation for the later interrupt-driven version.

## Run

Import the folder into STM32CubeIDE, build and flash it, then use the wiring from [the GPIO assignment report](../../document/es_03_lab_01.pdf).
