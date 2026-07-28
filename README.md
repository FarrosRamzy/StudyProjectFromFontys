# Study Projects from Fontys

This repository contains a selection of projects I completed during my 2 years of ICT studies at Fontys University of Applied Sciences. It includes personal assignments, team-based embedded systems projects, and my most recent full-stack internship project.

The projects reflect my development from small programming exercises to complete systems involving embedded hardware, backend services, databases, web applications, real-time communication, testing, and technical documentation.

## Project Collections

| Collection | Description |
|---|---|
| [Internship Projects](./InternshipProjects/) | My most recent work, including a full-stack hospital fixed-asset tracking system built with ESP32 sensor nodes, RFID, MQTT, FastAPI, PostgreSQL, React, and WebSocket communication. |
| [Group Projects](./GroupProjects/) | Team projects focused mainly on embedded systems, robotics, distributed communication, sensor integration, and hardware control. |
| [Personal Projects](./PersonalProjects/) | Individual assignments and experiments covering C, C++, C#, cybersecurity, STM32, PlatformIO, data structures, and desktop applications. |

## Featured Project

### Hospital Fixed-Asset Tracking System

My most recent project is a complete hospital asset-tracking platform designed to register, monitor, and manage movable hospital equipment using UHF RFID technology.

The system includes:

- ESP32-based Registration Desk and Checkpoint Nodes
- UHF RFID tag scanning and room-based asset detection
- MQTT communication between sensor nodes and the backend
- A FastAPI backend with PostgreSQL persistence
- A React Registration App for node, asset, user, and movement management
- A React Monitor App for live asset status, node status, alerts, and activity
- WebSocket-based live updates
- Role-based authentication and authorization
- Backend, frontend, firmware, integration, and end-to-end testing

The project documentation and setup instructions are available in the [Internship Projects folder](./InternshipProjects/).

## Group Project Highlights

The group-project collection includes:

- A distributed vehicle-control simulation using CAN bus
- An autonomous platooning robot using STM32 and ESP32
- An autonomous swarm robot with obstacle detection and MQTT telemetry
- A decentralized access and occupancy management system
- A distributed room-climate control system

For every group project, the project README explains the system briefly and separates my personal contribution from the work completed by the team.

## Personal Project Highlights

The personal-project collection includes:

- C programming assignments
- C++ data-structure implementations
- C# desktop applications
- Cybersecurity investigations and reports
- PlatformIO embedded projects
- STM32 GPIO, interrupts, SysTick, timer, input-capture, and PWM exercises

These smaller projects show the technical foundation that I later applied in the larger group and internship projects.

## Technologies

Across these projects, I have worked with:

- **Languages:** C, C++, C#, Python, JavaScript, SQL
- **Frontend:** React, Vite, HTML, CSS
- **Backend:** FastAPI, SQLAlchemy, REST APIs, WebSocket
- **Databases:** PostgreSQL, MongoDB
- **Embedded:** ESP32, STM32, Arduino, PlatformIO
- **Communication:** MQTT, CAN bus, UART, GPIO
- **Tools:** Git, GitHub, Visual Studio Code, Node-RED, MATLAB, PlantUML, pytest

## Repository Structure

```text
StudyProjectFromFontys/
├── GroupProjects/
│   └── README.md
├── InternshipProjects/
│   └── README.md
├── PersonalProjects/
│   └── README.md
└── README.md