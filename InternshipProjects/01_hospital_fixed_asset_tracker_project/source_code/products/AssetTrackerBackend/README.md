# Asset Tracker Backend

I built this FastAPI service as the central authority for the tracking system. The browser applications and sensor nodes do not update asset state directly. Their requests and MQTT messages are validated here before the backend changes the database or broadcasts a live event.

## Responsibilities

- First-admin setup, login, JWT sessions, and password hashing
- Role-based API authorization
- User account creation, role changes, activation, and password management
- Node discovery, enrollment, assignment, provisioning, identification, and lifecycle rules
- Asset registration, deregistration, querying, and deletion
- Movement request, cancellation, approval, rejection, and completion
- RFID detection and asset-flow resolution
- Offline-node detection from heartbeat timeouts
- MQTT settings, subscriptions, publishing, routing, and validation
- PostgreSQL persistence through SQLAlchemy
- Authenticated WebSocket snapshots and live updates
- Demo-data scripts for nodes and assets

## Architecture

```text
FastAPI routes
    -> authorization dependencies
    -> service and policy modules
    -> repositories / SQLAlchemy models
    -> PostgreSQL

MQTT worker
    -> topic and payload validation
    -> node / asset services
    -> database updates
    -> WebSocket broadcast service
```

The code is split into small route, service, repository, policy, serializer, and event-processing modules. Asset flow logic is further divided by states such as pending placement, movement requested, in transit, available, wrong location, and unauthorized movement.

## Main API areas

| Area | Main endpoints |
|---|---|
| Authentication | `/auth/setup-status`, `/auth/setup-admin`, `/auth/login`, `/auth/me`, `/auth/logout` |
| Users | `/users`, role and active-status updates, own password change, admin password reset |
| Nodes | `/nodes`, enrollment, assignment, provisioning, identification, unassignment, and deletion |
| Assets | `/assets`, registration, deregistration, deletion, and movement operations |
| Settings | `/settings/mqtt` and MQTT reconnect/reset operations |
| Realtime | `/ws` with a JWT token in the connection query |
| Service checks | `/` and `/health` |

The exact route behavior and role restrictions are defined in `app/routes` and enforced again in the service layer where necessary.

## Local setup

```bash
python -m venv .venv

# Windows
.venv\Scripts\activate

# Linux/macOS
source .venv/bin/activate

pip install -r requirements.txt
uvicorn app.main:app --reload --port 8010
```

The frontend defaults expect the backend on port `8010` during local development.

## Configuration

The backend reads deployment values from the environment. The main variables used by the current code are:

| Variable | Purpose |
|---|---|
| `DATABASE_URL` | PostgreSQL connection string; required |
| `JWT_SECRET_KEY` | JWT signing secret; required |
| `JWT_ALGORITHM` | JWT algorithm; defaults to HS256 |
| `JWT_ACCESS_TOKEN_EXPIRE_MINUTES` | Access-token lifetime |
| `APP_ENV` | Development or production behavior |
| `ENABLE_API_DOCS` | Enables or disables OpenAPI documentation |
| `MQTT_BROKER`, `MQTT_PORT` | Default broker connection |
| `MQTT_USERNAME`, `MQTT_PASSWORD` | Optional broker authentication |
| `MQTT_TLS_ENABLED` | MQTT TLS setting |
| `MQTT_TOPIC_NAMESPACE` | Hospital or deployment topic namespace |
| `MQTT_CLIENT_ID` | Backend MQTT client identifier |
| `NODE_PROVISIONING_KEY` | Protects node provisioning requests |
| `NODE_OFFLINE_TIMEOUT_SECONDS` | Heartbeat timeout |
| `NODE_STATUS_CHECK_INTERVAL_SECONDS` | Offline-monitor interval |
| `DUMMY_NODES_STAY_ONLINE`, `DUMMY_NODE_PREFIX` | Controlled demo-node behavior |

I do not include real values in this repository documentation.

## Database model

The main persisted records are:

- users;
- nodes;
- assets;
- asset events and detections;
- movement requests;
- system settings.

The current snapshot creates missing tables through SQLAlchemy metadata during startup. For production, I would add a formal migration tool and deployment migration step.

## MQTT and WebSocket behavior

The backend subscribes to topics shaped like:

```text
<namespace>/nodes/<device-id>/rfid/asset-registration
<namespace>/nodes/<device-id>/rfid/detected
<namespace>/nodes/<device-id>/heartbeat
<namespace>/nodes/<device-id>/status
<namespace>/nodes/<device-id>/commands/ack
```

Commands such as physical node identification are published to the target node. After a valid event changes system state, the backend broadcasts a structured WebSocket message to authenticated clients.

## Tests

The repository contains unit, service, and route tests for authentication, setup locking, admin safety, user access, node lifecycle, asset registration, movement decisions, MQTT topics, and flow-state behavior.

```bash
pytest
pytest tests/unit
pytest tests/services
pytest tests/routes
```

The current snapshot contains 44 test modules and 147 test functions.

## Demo scripts

The `scripts` folder can create and remove dummy assets and nodes and simulate asset movement. These scripts are intended for development and demonstrations, not production data.

Examples:

```bash
python scripts/seed_dummy_nodes.py
python scripts/seed_dummy_assets.py
python scripts/move_dummy_assets.py
python scripts/cleanup_dummy_assets.py
python scripts/cleanup_dummy_nodes.py
```

## Current implementation notes

- CORS origins are currently listed in `app/main.py` and should be deployment-configurable before reuse.
- The MQTT worker starts with the FastAPI application. Multiple backend replicas require explicit MQTT-worker ownership or coordination.
- `render.yaml` is empty in this snapshot, so the cloud service configuration is maintained outside this folder.
- Local database files and real environment values should not be committed.
