# System Design Assets

This folder contains the diagrams I created while designing the Hospital Fixed-Asset Tracking System.

## Folder layout

- [`design_editor/`](./design_editor/) contains editable Visio, PlantUML, Fritzing, and related source files.
- [`released_design/`](./released_design/) contains the exported diagrams used in the project documentation.
- [`unit_test_screenshot/`](./unit_test_screenshot/) contains selected test evidence images.

## Diagram groups

The released design set covers:

- system context and high-level architecture;
- communication between web applications, backend, MQTT, nodes, and database;
- deployment of browser clients, cloud services, and sensor nodes;
- entity relationships for users, settings, nodes, assets, detections, movements, alerts, and activity;
- firmware classes and interfaces;
- use-case diagrams;
- sequence diagrams;
- firmware and application state machines;
- subsystem responsibilities;
- hardware wiring.

For a quick overview, start with:

1. [`released_design/001-Fixed Context Diagram.png`](./released_design/001-Fixed%20Context%20Diagram.png)
2. [`released_design/system_architecture_diagram.jpg`](./released_design/system_architecture_diagram.jpg)
3. [`released_design/communication_flow/000-0_complete_communication_flow.png`](./released_design/communication_flow/000-0_complete_communication_flow.png)
4. [`released_design/entity_relation_diagrams/001-0_overall_system_erd.png`](./released_design/entity_relation_diagrams/001-0_overall_system_erd.png)
5. [`released_design/deployment_diagrams/001-1_hospital_fixed_asset_deployment_diagram.png`](./released_design/deployment_diagrams/001-1_hospital_fixed_asset_deployment_diagram.png)

The editable files are useful when changing the design. The exported files are better for reading, reviews, and repository previews.
