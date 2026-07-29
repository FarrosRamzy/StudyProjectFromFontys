# Timer PWM Output Projects

These three projects show my progression with STM32 timer output compare and PWM:

- [Fixed PWM LED](./source_code/timers_output_a/) generates a constant 75% duty cycle.
- [Pulsing PWM LED](./source_code/timers_output_b/) changes the compare value in a timer interrupt to create a breathing effect.
- [PWM Servo Control](./source_code/timers_output_c/) generates servo pulses and cycles through three angular positions.

The timer setup, calculations, and logic-analyzer results are available in [the PWM output report](./document/es_03_lab_04.pdf).
