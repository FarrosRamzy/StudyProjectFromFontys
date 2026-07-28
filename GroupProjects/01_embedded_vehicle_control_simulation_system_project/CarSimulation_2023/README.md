# Embedded Vehicle Control Simulation

In this project, I worked with three teammates to build a small distributed vehicle-control prototype. Instead of putting every function on one microcontroller, we separated the system into several controllers and connected them through a CAN bus.

The prototype includes a dashboard, an engine controller, a headlight and indicator controller, a pressure and temperature controller, and a remote communication controller. The remote controller uses an ESP32 and MQTT so selected vehicle functions can also be controlled or monitored remotely.

## How the System Works

```text
Remote client / MQTT broker
            │
            ▼
          RCC
            │
            ▼
Dashboard ─ CAN bus ─ Engine
            │
          HIC / PTC
```

- The **Dashboard** reads driver inputs and displays information.
- The **Engine** handles the simulated engine and servo behavior.
- The **HIC** controls headlights and turn indicators.
- The **PTC** reads pressure and temperature data and sends warnings.
- The **RCC** translates MQTT commands into CAN messages and publishes selected sensor data remotely.

## My Contribution

I mainly worked on the **Remote Controller Communication (RCC)** and **Pressure and Temperature Communication (PTC)** subsystems.

My contribution included:

- developing the RCC communication flow between MQTT and CAN;
- working on the pressure and temperature sensor communication;
- helping create the shared CAN manager used by the different controllers;
- implementing a large part of the headlight and indicator command logic;
- helping integrate messages between the RCC, dashboard, HIC, PTC, and engine controllers.

This project gave me practical experience with distributed embedded systems, shared communication protocols, and integrating separately developed modules into one working prototype.

## Main Technologies

- C++
- Arduino framework
- ESP32 and Arduino Uno
- PlatformIO
- CAN bus
- MQTT and PubSubClient
- BME280 pressure and temperature sensor
- LCD, LEDs, buttons, and servo motors

## Repository Structure

```text
CarSimulation_2023/
├── Dashboard/   # Driver input, LCD, and CAN communication
├── Engine/      # Engine and servo behavior
├── HIC/         # Headlight and indicator controller
├── PTC/         # Pressure and temperature controller
└── RCC/         # MQTT remote controller and CAN bridge
```

Each folder is an independent PlatformIO project.

## Building a Subsystem

For example, to build the RCC project:

```bash
pio run -d RCC
```

To upload it:

```bash
pio run -d RCC -t upload
```

The complete demonstration requires the original boards, CAN modules, sensors, actuators, and wiring. Local Wi-Fi and MQTT settings should be stored outside the committed source code before the repository is published.
