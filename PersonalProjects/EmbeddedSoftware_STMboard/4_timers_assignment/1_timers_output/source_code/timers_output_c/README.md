# PWM Servo Control

I used TIM2 PWM to control a hobby servo connected to PA9. The timer produces a 20 ms servo period, while the compare value determines the pulse width and therefore the requested angle.

The firmware cycles through -90, 0, and +90 degrees. A timer interrupt changes the target approximately once per second, and `Set_Rotation_Level()` converts the requested angle into the corresponding pulse width.

## What I implemented

- TIM2 channel-3 PWM
- PA9 alternate-function configuration
- 20 ms servo period
- Angle-to-pulse conversion
- Interrupt-driven sequence for left, center, and right positions

## Run

Connect a compatible servo, open the project in STM32CubeIDE, and flash the board. The original timing measurements are shown in [the timer output report](../../document/es_03_lab_04.pdf).
