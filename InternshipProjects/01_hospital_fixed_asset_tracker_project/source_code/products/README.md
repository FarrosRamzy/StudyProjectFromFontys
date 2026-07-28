# Integrated Product Source Code

This folder contains the four components I use for the current Hospital Fixed-Asset Tracking System.

```text
RFID Reader -> ESP32 Sensor Node -> MQTT Broker -> FastAPI Backend
                                                    |        |
                                               PostgreSQL  WebSocket
                                                    |        |
                                      Registration App   Monitor App
```

## Components

| Component | Purpose |
|---|---|
| [`AssetTrackerBackend`](./AssetTrackerBackend/) | API, authentication, database access, MQTT processing, business rules, and WebSocket broadcasting |
| [`AssetTrackerRegistrationFrontEnd`](./AssetTrackerRegistrationFrontEnd/) | Administrative, node-registration, asset-registration, movement-decision, user, and settings workflows |
| [`AssetTrackerMonitorFrontEnd`](./AssetTrackerMonitorFrontEnd/) | Asset and node monitoring, alerts, activity, and movement requests |
| [`AssetTrackerSensorNode`](./AssetTrackerSensorNode/) | ESP32 firmware for Registration Desk and Checkpoint Nodes |

## Recommended local startup order

### 1. Start PostgreSQL and an MQTT broker

Create a local PostgreSQL database and make sure the MQTT broker is reachable by the backend and sensor nodes.

### 2. Start the backend

```bash
cd AssetTrackerBackend
python -m venv .venv

# Windows
.venv\Scripts\activate

# Linux/macOS
source .venv/bin/activate

pip install -r requirements.txt
uvicorn app.main:app --reload --port 8010
```

The backend requires at least a database connection and JWT secret. MQTT, node timeout, documentation, and deployment behavior are also configurable. Keep all real values outside Git.

### 3. Start the Registration App

```bash
cd ../AssetTrackerRegistrationFrontEnd
npm ci
npm run dev -- --port 5173
```

Configure `VITE_API_BASE_URL` and, when needed, `VITE_WS_BASE_URL`. The app can derive the WebSocket URL from the API URL when a separate value is not supplied.

### 4. Start the Monitor App

```bash
cd ../AssetTrackerMonitorFrontEnd
npm ci
npm run dev -- --port 5174
```

Configure `VITE_API_BASE_URL` and `VITE_WS_BASE_URL` for the same backend.

### 5. Build and provision a sensor node

```bash
cd ../AssetTrackerSensorNode
pio run
pio run --target buildfs
pio run --target uploadfs --upload-port <PORT>
pio run --target upload --upload-port <PORT>
pio device monitor --port <PORT> --baud 115200
```

The node first needs Wi-Fi and backend provisioning information through its local setup page. After assignment, its role determines whether RFID scans are published as registration scans or checkpoint detections.

## First use

1. Open the Registration App.
2. Create the first admin account if the database is new.
3. Configure or confirm the MQTT settings.
4. Power a sensor node and complete its Wi-Fi setup.
5. Enroll and assign the node as Registration Desk or Checkpoint.
6. Register an asset and select its expected room.
7. Detect the asset at a checkpoint to complete initial placement.
8. Open the Monitor App to review assets, nodes, warnings, and activity.

## Validation commands

```bash
# Backend tests
cd AssetTrackerBackend
pytest

# Registration frontend
cd ../AssetTrackerRegistrationFrontEnd
npm run lint
npm run build

# Monitor frontend
cd ../AssetTrackerMonitorFrontEnd
npm run lint
npm run build

# Firmware native tests
cd ../AssetTrackerSensorNode
pio test -e native
```

Do not commit `.env` files, dependency folders, build output, virtual environments, firmware build caches, or local test databases.
