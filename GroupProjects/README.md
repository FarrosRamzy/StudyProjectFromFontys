# Embedded and Distributed Systems Projects

This repository contains a collection of group projects I completed during my ICT studies. Most of the projects combine embedded software with sensors, actuators, communication protocols, and a user interface or dashboard.

I use this repository to show how I approach embedded-system development: dividing a larger problem into smaller modules, connecting multiple devices, testing hardware behavior, and integrating the result into one working prototype.

Because these were team projects, each project README briefly explains both the complete system and the parts I personally worked on.

## Projects

| Project | Brief description | Main technologies |
|---|---|---|
| [Embedded Vehicle Control Simulation](./01_embedded_vehicle_control_simulation_system_project/CarSimulation_2023/) | A vehicle prototype divided into several controllers that communicate over CAN, with an ESP32 MQTT bridge for remote commands. | C++, Arduino, ESP32, CAN, MQTT, PlatformIO |
| [Autonomous Platooning Robot](./02_autonomous_robot_simulation_system_project/PlatooningRobot_2024/) | A track-following robot that maintains a safe distance and sends telemetry to a Node-RED dashboard. | STM32, ESP32, C/C++, UART, MQTT, Node-RED |
| [Autonomous Swarm Robot](./02_autonomous_robot_simulation_system_project/SwarmRobot_2023/) | A mobile robot that detects obstacles, slows down, reverses, and turns automatically. | STM32, ESP32, C/C++, MQTT, Node-RED |
| [Decentralized Access and Occupancy System](./03_decentralized_access_%26_occupancy_communication_system_project/OccupancyManagement/) | A multi-gate system that tracks occupancy, estimates queues, and coordinates emergency behavior through MQTT. | ESP32, C++, MQTT, servos, LCD |
| [Room Climate Control System](./04_decentralized_room_climate_control_project/RoomClimateControl/) | A room-monitoring prototype that reads climate sensors, controls ventilation, and displays data locally and in a desktop application. | Arduino, ESP, Nextion, C++, C#, MongoDB |

## What These Projects Demonstrate

- Embedded C and C++ development
- Arduino, ESP32, ESP8266, and STM32 development
- Sensor reading and actuator control
- CAN, UART, Wi-Fi, MQTT, and TCP communication
- State-machine and modular software design
- PlatformIO and STM32CubeIDE workflows
- Node-RED dashboards
- Nextion touchscreen development
- C# Windows Forms development
- Hardware/software integration and testing

## Repository Note

These folders are historical academic project snapshots. Some contain generated build files, older experiments, or local configuration values. Before publishing the repository, I would remove generated artifacts, move credentials into ignored local configuration files, and rotate any credentials that were previously committed.
