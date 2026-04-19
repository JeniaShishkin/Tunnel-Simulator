# Drone Simulator

This project is a drone simulation application built with a strong focus on maintainable architecture and iterative development.

## Key Principles

- **SOLID design** drives the code structure:
  - Single Responsibility: each class and module has a clear, focused purpose.
  - Open/Closed: components are designed for extension without modification.
  - Liskov Substitution: abstractions are used so implementations can be swapped safely.
  - Interface Segregation: interfaces are kept minimal and specific.
  - Dependency Inversion: high-level components depend on abstractions, not concrete classes.

- **Agile methodology** guides development:
  - Incremental improvements and frequent refactoring.
  - Responsive adaptation to requirements.
  - Emphasis on working code, collaboration, and continuous enhancement.

## Project Structure

The project is organized into the following folders and files:

### Root Files
- `BaseEssentials.h` — Base utilities and essentials
- `Drone.cpp` — Drone class implementation
- `Drone.h` — Drone class header
- `main.cpp` — Simulation entry point
- `README.md` — This file

### Cmd/ Folder
Contains command classes for controlling the drone:
- `Command.h` — Abstract base class for commands
- `Context.h` — Context for command execution
- `Execute.cpp`, `Execute.h` — Execute command (runs a function)
- `Forward.cpp`, `Forward.h` — Forward command (moves drone forward)
- `Map.cpp`, `Map.h` — Map command (displays the world grid)
- `PointOfView.cpp`, `PointOfView.h` — PointOfView command (shows drone's view)
- `SetSensor.h` — SetSensor command (sets active sensor)
- `TurnLeft.cpp`, `TurnLeft.h` — TurnLeft command (turns drone left)
- `TurnRight.cpp`, `TurnRight.h` — TurnRight command (turns drone right)

### Navigation/ Folder
Handles navigation and positioning:
- `Compass.cpp`, `Compass.h` — Compass class for direction
- `Position.cpp`, `Position.h` — Position class for coordinates
- `WorldGrid.cpp`, `WorldGrid.h` — WorldGrid class for the simulation environment

### Sensors/ Folder
Sensor implementations for obstacle detection:
- `CircularSensor.cpp`, `CircularSensor.h` — Circular sensor
- `DistanceSensor.cpp`, `DistanceSensor.h` — Distance sensor
- `Sensor.h` — Abstract base sensor class
- `WideSensor.cpp`, `WideSensor.h` — Wide sensor

### Tiles/ Folder
Tile types for the world grid:
- `EmptyTile.cpp`, `EmptyTile.h` — Empty tile
- `ExitTile.h` — Exit tile
- `Tile.cpp`, `Tile.h` — Abstract base tile class
- `WallTile.h` — Wall tile

## Existing Commands

The simulation supports the following commands for controlling the drone:

- **Forward**: Moves the drone one step forward in its current direction, checking for obstacles.
- **TurnLeft**: Rotates the drone 90 degrees to the left.
- **TurnRight**: Rotates the drone 90 degrees to the right.
- **Map**: Displays the entire world grid.
- **PointOfView**: Shows what the drone can see from its current position and orientation.
- **SetSensor**: Creates a sensor for obstacle detection.
- **Execute**: Executes a custom function or operation.

## Goal

This repository is intended as an example of building a small system with clean, extensible design while following agile development practices and SOLID principles.
