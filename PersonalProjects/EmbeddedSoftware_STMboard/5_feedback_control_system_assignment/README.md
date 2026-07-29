# Feedback Control System Assignment

I used this assignment to study PID control for a moving robot and translate the control calculation into embedded C.

I first explored the proportional, integral, and derivative behavior and used MATLAB/Simulink to investigate tuning and oscillation. I then wrote a firmware-side PID function that calculates the error, accumulates the integral term, derives the rate of change, combines the three terms, and limits the output.

The implementation in this repository is a control-algorithm prototype: `measure_distance()` is still a placeholder, so it demonstrates the PID structure but is not a complete closed-loop hardware system.

- [PID Prototype Source](./source_code/feedback_control_system/)
- [Assignment Report](./document/es_03_lab_06.pdf)
