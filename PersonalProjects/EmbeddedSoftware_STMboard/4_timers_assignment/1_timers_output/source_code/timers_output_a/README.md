# Fixed PWM LED Output

I built this exercise to generate a hardware PWM signal with TIM2 rather than switching an LED manually in the main loop.

TIM2 channel 2 is routed to PB3 through the alternate-function register. The timer uses a one-millisecond PWM period, and the compare register is set to 750 out of 1000, producing a fixed 75% duty cycle.

## What I implemented

- TIM2 clock, prescaler, period, and counter setup
- PWM mode on channel 2
- PB3 alternate-function configuration
- Fixed duty-cycle control through `CCR2`

## Run

Open the project in STM32CubeIDE, build and flash it, then connect the LED as described in [the timer output report](../../document/es_03_lab_04.pdf).
