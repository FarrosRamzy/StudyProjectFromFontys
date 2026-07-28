# Asset Tracker Monitor App

I built this React application as the operational view of the tracking system. It gives users a quick way to see where assets were last detected, whether sensor nodes are available, which movements are pending, and which warnings need attention.

## Main features

- Authenticated access for Admin, Test User, and Monitor Staff accounts
- Dashboard summaries for assets, nodes, warnings, and recent activity
- Asset location, assigned room, last-seen time, and flow-state monitoring
- Search, filtering, sorting, pagination, and asset detail views
- Movement request creation and eligible request cancellation
- Destination checkpoint search and movement validation feedback
- Node role, room, status, and heartbeat monitoring
- Unknown-tag, offline-node, and asset-movement warnings
- Activity log for important asset, node, movement, and system events
- WebSocket snapshots, live updates, connection status, and reconnection handling
- Responsive desktop and mobile layouts

## Application areas

| Page | Purpose |
|---|---|
| Dashboard | System health, operational totals, warnings, and recent activity |
| Assets | Current and expected locations, flow status, details, and movement actions |
| Nodes | Checkpoint and Registration Desk availability |
| Alerts | Unknown tags, offline nodes, and abnormal asset states |
| Activities | User-facing history of important system events |

## Project structure

```text
src/
├── components/     # Tables, modal, drawer, dashboard, layout, and common UI
├── constants/      # Routes, statuses, metadata, and WebSocket event names
├── hooks/          # Authentication, data loading, filters, sorting, movement, and sockets
├── pages/          # Dashboard, Assets, Nodes, Alerts, Activity, and Login
├── services/       # API, authentication, asset, node, and WebSocket clients
├── styles/         # Shared, component, page, modal, table, and responsive CSS
└── utils/          # Status, alert, activity, date, search, and access helpers
```

The app performs initial and recovery loading through the HTTP API. WebSocket messages then update the active collections without replacing the persistent backend as the source of truth.

## Local setup

```bash
npm ci
npm run dev -- --port 5174
```

Configuration names:

| Variable | Purpose |
|---|---|
| `VITE_API_BASE_URL` | Backend HTTP base URL; local fallback is `http://localhost:8010` |
| `VITE_WS_BASE_URL` | Authenticated WebSocket endpoint; local fallback is `ws://localhost:8010/ws` |

## Useful commands

```bash
npm run dev
npm run lint
npm run build
npm run preview
```

## Movement workflow

From the Assets page, an authorized user can select an eligible asset, search for a destination checkpoint, enter a reason, and submit a movement request. The Registration App is responsible for approving or rejecting it. After approval, the backend waits for the destination checkpoint detection before completing the movement.

## Current implementation notes

- The app uses an internal page state rather than URL routes for its monitoring modules.
- The repository includes linting and production builds but no automated browser test suite in this snapshot.
- The package metadata still contains an early template package name.
- Live updates require a valid JWT and a working backend WebSocket connection.
