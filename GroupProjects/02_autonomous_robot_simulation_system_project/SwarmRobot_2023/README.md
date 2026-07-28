# Autonomous Swarm Robot

In this project, my team built a wheeled robot that can detect an obstacle, reduce its speed, stop before a collision, reverse, and turn in a new direction automatically.

An STM32 controller reads the ultrasonic sensor and controls the wheel servos. An ESP32 receives robot information through UART and publishes it through MQTT so the distance and robot state can be displayed in a Node-RED dashboard.

## How the System Works

```text
Ultrasonic sensor ─ STM32 ─ wheel servos
                         │
                        UART
                         ▼
                       ESP32 ─ MQTT ─ Node-RED
```

The robot follows a state-based control flow:

```text
Initialize → Move → Stop → Reverse → Turn → Move
```

While moving, the controller adjusts motor power based on the measured distance. When an obstacle becomes too close, the robot stops, reverses for a short period, and turns before moving again.

## My Contribution

My documented contribution was mainly in the low-level STM32 configuration used by the robot.

I worked on:

- the STM32 GPIO module used by the ultrasonic sensor and robot outputs;
- the STM32 timer configuration used for sensor timing and servo control.

The archive does not contain a complete per-person task record for the remaining modules, so I have limited this section to the contribution that can be verified from the source files.

Through this project, I gained experience with timer-based sensor measurements, motor control, embedded state machines, and communication between two microcontrollers.

## Main Technologies

- Embedded C and C++
- STM32F303RE Nucleo
- ESP32
- STM32CubeIDE
- PlatformIO
- UART and MQTT
- Node-RED
- Ultrasonic sensor
- Continuous-rotation servo motors

## Repository Structure

```text
SwarmRobot_2023/
├── code/
│   ├── swarm_robot_v2/               # STM32 movement controller
│   ├── robot_dashboard_communicator/ # ESP32 MQTT gateway
│   └── node-red/                     # Dashboard flow
└── doc/                              # Reports and hardware information
```

## Running the Projects

Open `code/swarm_robot_v2/` in STM32CubeIDE to build and flash the STM32 firmware.

Build the ESP32 project with:

```bash
pio run -d code/robot_dashboard_communicator
```

Import the JSON file from `code/node-red/` into Node-RED to restore the dashboard.

The robot must be recalibrated when different motors, sensors, power supplies, or mechanical parts are used. Wi-Fi and MQTT credentials should also be moved out of committed source files.
