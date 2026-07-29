# Pulsing PWM LED

I extended the fixed-PWM exercise into a breathing LED. TIM2 generates the PWM signal on PB3, and its channel interrupt gradually increases and decreases the compare value.

The brightness moves between the configured minimum and maximum levels, creating a smooth fade without using a blocking delay in the main loop.

## What I implemented

- TIM2 channel-2 PWM on PB3
- Timer interrupt and NVIC configuration
- Incrementing and decrementing duty-cycle state
- Compare-register updates inside `TIM2_IRQHandler()`
- Continuous animation with an empty main loop

## Run

Import, build, and flash the project with STM32CubeIDE. The PWM calculation and observed waveform are documented in [the timer output report](../../document/es_03_lab_04.pdf).
