# Two-Controller Traffic Light System

I created this project to reproduce a basic traffic-light intersection using two Arduino Uno boards. One board acts as the master and the other as the slave, with serial communication keeping their states coordinated.

## Behaviour

- The two traffic lights follow a safe timed sequence.
- Their normal states remain complementary so conflicting traffic does not receive green at the same time.
- Both controllers can enter a blinking-orange inactive or fault mode.
- After ten seconds, the system automatically returns to the normal sequence while power remains available.

I implemented the master and slave programs, LED-state logic, traffic sequence, and communication between the boards.

The included PNG files show the master and slave wiring layouts.
