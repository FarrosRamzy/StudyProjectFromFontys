# Asset Tracker Registration App

I built this React application for the administrative and registration side of the system. It guides users through setup, node management, asset registration, movement decisions, user administration, and system configuration while leaving final authorization and business-rule enforcement to the backend.

## Main features

- First-admin setup for a new database
- Login, session restoration, logout, and expired-session handling
- Role-aware dashboard and protected routes
- Node discovery, assignment, editing, identification by blink, unassignment, and deletion
- RFID-based asset registration and deregistration
- Asset search, sorting, status display, and pagination
- Movement request review, approval, and rejection
- User creation, role changes, account activation, and password reset
- Personal password change
- MQTT/system settings view and update
- WebSocket updates for nodes, assets, scans, and movements
- Responsive layouts for desktop, half-window, tablet, and mobile use

## Role access

| Page | Roles |
|---|---|
| Dashboard and own password | All authenticated roles |
| Node Registration | Admin, Test User, Technician |
| Asset Registration | Admin, Test User, Registration Staff |
| User Management | Admin |
| System Settings | Admin, Test User |

The frontend hides unavailable routes and actions, but the backend remains authoritative.

## Project structure

```text
src/
├── components/     # Forms, tables, cards, badges, navigation, and layout
├── context/        # Authentication context
├── hooks/          # Page state, actions, sockets, sorting, and pagination
├── pages/          # Routed application pages
├── routes/         # Setup-aware and role-protected routing
├── services/       # API, authentication, settings, asset, node, and user clients
├── styles/         # Shared, page, component, layout, and responsive CSS
└── utils/          # Formatting, validation, policies, and payload helpers
```

I kept page components focused on composition and moved reusable behavior into hooks, services, and utilities.

## Local setup

```bash
npm ci
npm run dev -- --port 5173
```

The application uses these Vite configuration names:

| Variable | Purpose |
|---|---|
| `VITE_API_BASE_URL` | Backend HTTP base URL; local fallback is `http://localhost:8010` |
| `VITE_WS_BASE_URL` | Backend WebSocket URL or base |
| `VITE_WS_URL` | Backward-compatible WebSocket setting used when the base value is absent |

Keep local and production values outside source control.

## Useful commands

```bash
npm run dev
npm run lint
npm run build
npm run preview
```

## How I use the app

1. On a fresh database, I create the first admin account.
2. I sign in and confirm the MQTT settings.
3. I assign discovered sensor nodes to their roles and locations.
4. I scan a tag at an online Registration Desk Node and register the asset.
5. I review pending movement requests and approve or reject them.
6. I manage users and account safety through the admin-only page.

## Current implementation notes

- The project is written in JavaScript rather than TypeScript.
- The repository provides linting and production builds but no automated browser test suite in this snapshot.
- The package metadata still contains an early template package name; the application behavior and folder name reflect its actual purpose.
- Production hosting must provide a single-page-application rewrite so direct route navigation returns `index.html`.
