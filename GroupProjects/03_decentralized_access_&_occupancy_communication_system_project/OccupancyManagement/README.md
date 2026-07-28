# Decentralized Access and Occupancy Management System

In this group project, we built a decentralized gate system for managing access, occupancy, queues, and emergency behavior in a building.

The goal was to avoid depending on one master controller. Each gate can handle its own buttons, servo, and queue sensors, while MQTT is used to share occupancy information and coordinate the other nodes. A separate ESP32 and LCD display show the current occupancy, fastest queue, emergency state, and gate-connection warnings.

## How the System Works

```text
Gate 1 ─┐
Gate 2 ─┼── MQTT ── occupancy display
Gate 3 ─┘
```

Each gate can:

- open and close using a servo;
- count entries and exits;
- report its estimated queue;
- respond to an emergency command;
- share occupancy and status information with the other devices.

The display controller rotates between occupancy, queue, emergency, full-building, and disconnected-gate messages.

## My Contribution

I participated in this project as a member of the design and development team. However, the supplied archive does not preserve a reliable per-person task breakdown, and some source comments attribute specific code sections to other teammates.

For that reason, I have not assigned individual code modules to myself in this README. What I can say clearly is in this project, multiple developers in the group were mostly working on the same files by turns. But as a personal contribution, I was fully focused on the communication protocol, system data integration and LCD UI development.

This project still demonstrates my experience working in a team on a distributed embedded system in which several independently operating devices must keep shared information synchronized.

## Main Technologies

- C++ and Arduino framework
- ESP32 / NodeMCU-32S
- PlatformIO
- MQTT
- Servo motors
- 16x2 LCD
- Buttons and pressure-plate inputs

## Repository Structure

```text
OccupancyManagement/
├── ESP industry/          # Gate and queue controller
├── lcd_esp_device_new/    # Occupancy and emergency display
└── Documents/             # Requirements, protocol, research, and overview
```

## Building the Projects

Build the gate controller with:

```bash
pio run -d "ESP industry"
```

Build the display controller with:

```bash
pio run -d lcd_esp_device_new
```

A complete multi-gate demonstration requires a unique MQTT identity and topic configuration for each gate. The historic Wi-Fi and MQTT values in the source should be removed and rotated before this repository is made public.
