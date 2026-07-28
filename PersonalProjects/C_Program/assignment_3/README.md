# Data Transmission Encoder and Decoder

I created this project to simulate a small data-transmission pipeline. An encoder protects the input, a channeler introduces controlled corruption, and a decoder checks and repairs the transmitted data.

## What I implemented

- A file encoder that adds parity information.
- A channeler that simulates transmission errors by flipping bits.
- A decoder that detects and corrects supported errors.
- File-based input, encoded, transmitted, and output data.
- Unit tests for the three processing stages.

This project helped me understand parity, error detection, bit manipulation, and the separation of a larger workflow into independent programs.
