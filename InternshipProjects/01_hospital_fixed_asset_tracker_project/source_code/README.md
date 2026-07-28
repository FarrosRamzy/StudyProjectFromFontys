# Source Code

This folder contains the implementation history of the Hospital Fixed-Asset Tracking System.

## Current implementation

The integrated and most recent project version is stored in [`products/`](./products/). It contains the backend, both web applications, and the ESP32 firmware that are designed to work together.

```text
products/
├── AssetTrackerBackend/
├── AssetTrackerRegistrationFrontEnd/
├── AssetTrackerMonitorFrontEnd/
└── AssetTrackerSensorNode/
```

## Earlier frontend iterations

The following folders are standalone development iterations that were created before the current applications were consolidated under `products`:

- `NodeProvisionFrontEnd`
- `AssetRegistrationFrontEnd`
- `AssetAndNodeMonitorApp`

I kept them as development history, but they should not be mixed with the current integrated stack when running or demonstrating the project.

Start with [`products/README.md`](./products/README.md).
