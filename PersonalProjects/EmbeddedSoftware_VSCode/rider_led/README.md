# Rider LED and Independent Blink

I built this embedded assignment to demonstrate bit manipulation through a row of LEDs while keeping a separate LED blinking independently.

## Behaviour

- One LED continues blinking at a stable rate.
- When the button is released, one active LED sweeps across the row.
- When the button is pressed, a multi-LED sweep pattern is used.
- Changing the sweep pattern must not interrupt the independent blinking LED.

I implemented the LED masks, sweep logic, button handling, and timing behaviour. The main challenge was updating the correct output bits without affecting unrelated LEDs.
