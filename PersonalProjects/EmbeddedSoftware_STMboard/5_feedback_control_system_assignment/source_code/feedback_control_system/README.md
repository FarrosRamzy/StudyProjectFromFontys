# PID Control Prototype

I wrote this project as the firmware skeleton for a distance-based PID controller. The intended use is to adjust a robot's output as its measured distance approaches a target obstacle distance.

The `my_pid()` function calculates proportional, integral, and derivative terms, remembers the previous error, resets the integral in selected conditions, and clamps the final output to a configured maximum.

## What I implemented

- Configurable target distance and output limit
- Proportional, integral, and derivative calculations
- Persistent integral and previous-error state
- Output limiting to reduce excessive control commands
- A main-loop integration point for distance measurement

## Current status

This is a prototype rather than a completed hardware controller. The included `measure_distance()` function returns a placeholder value and must be connected to a real sensor implementation before the loop can control a motor or servo.

## Background

I used MATLAB/Simulink and PID-tuning exercises to explore controller behavior before writing the embedded-code structure. The reasoning and tuning process are documented in [the feedback-control report](../../document/es_03_lab_06.pdf).
