# Ultrasonic Distance Measurement with Input Capture

I built this project to measure distance with an HC-SR04 sensor using STM32 hardware timers instead of software pulse timing.

TIM3 channel 2 produces the trigger signal on PB5. TIM4 channel 1 captures the echo signal on PB6, switching between rising and falling edges to calculate the pulse width. The handler also accounts for timer wraparound. The measured pulse is converted to centimeters and printed through USART2 every 500 ms.

## What I implemented

- TIM3 PWM trigger generation
- TIM4 input capture and interrupt handling
- Rising- and falling-edge pulse measurement
- Timer-overflow compensation
- Distance conversion from echo duration
- Custom SysTick millisecond counter
- USART2 output at 9600 baud

## Hardware

- STM32 Nucleo-F303RE
- HC-SR04 ultrasonic sensor
- Breadboard and jumper wires
- Serial terminal

## Run

Import the project into STM32CubeIDE, build and flash it, connect the sensor to PB5 and PB6 according to [the timer input report](../../document/es_03_lab_05.pdf), and open a 9600-baud serial terminal to view the measurements.
