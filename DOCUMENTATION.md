# Ping Pong Documentation

## Table of Contents
- [Overview](#overview)
- [Project Structure](#project-structure)
- [Core Components](#core-components)
  - [Main Application](#main-application)
  - [Entity System](#entity-system)
  - [Scene Management](#scene-management)
  - [UI Elements](#ui-elements)
- [Game Mechanics](#game-mechanics)
  - [Controls](#controls)
  - [Game Modes](#game-modes)
  - [Scoring System](#scoring-system)
- [Technical Implementation](#technical-implementation)
  - [Dependencies](#dependencies)
  - [Audio System](#audio-system)
  - [Graphics Rendering](#graphics-rendering)
- [Build and Execution](#build-and-execution)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
  - [Running the Game](#running-the-game)

## Overview

This project implements a classic **Ping Pong** game using **C++** and the **Raylib** graphics library. The game features both _single-player mode_ against an AI opponent and _two-player mode_ for local multiplayer competition.

The implementation follows **object-oriented programming principles** with a clear separation of concerns between game entities, scenes, and UI components.

## Project Structure

```
└── 📁 src
    ├── 📄 main.cpp (590 Bytes)
    ├── 📁 UI
    │   ├── 📄 ELement.h (1022 Bytes)
    │   └── 📄 Button.cpp (1.61 KB)
    ├── 📁 Scenes
    │   ├── 📄 Scenes.h (1.72 KB)
    │   ├── 📄 Play.cpp (2.16 KB)
    │   ├── 📄 PauseMenu.cpp (1.13 KB)
    │   ├── 📄 Manager.h (617 Bytes)
    │   ├── 📄 Manager.cpp (827 Bytes)
    │   └── 📄 MainMenu.cpp (1008 Bytes)
    ├── 📁 Entities
    │   ├── 📄 Player2.cpp (870 Bytes)
    │   ├── 📄 Player1.cpp (370 Bytes)
    │   ├── 📄 Entity.h (1.83 KB)
    │   └── 📄 Ball.cpp (2.9 KB)
    └── 📁 Assets
        ├── 📁 Textures
        │   ├── 📄 t_pauseLogo.psd (532.7 KB)
        │   ├── 📄 t_pauseLogo.png (15.28 KB)
        │   ├── 📄 t_logo.psd (602.79 KB)
        │   └── 📄 t_logo.png (23.02 KB)
        ├── 📁 Sounds
        │   ├── 📄 hoverButton.wav (86.85 KB)
        │   ├── 📄 collision.wav (15.88 KB)
        │   ├── 📄 bg.wav (10.13 MB)
        └── 📁 Fonts
            └── 📄 NotoSansJP-Regular.ttf (5.2 MB)
```

## Core Components

### Main Application

**File:** `main.cpp`

The entry point initializes a `1200x800` window titled **"Ping Pong"**. It sets up the audio system and runs at `120 FPS` for smooth gameplay. The main loop continuously renders and updates the current scene managed by the `SceneManager`.

### Entity System

_Defined in_ `Entity.h`

#### Base Entity Class

Abstract foundation for all game objects with:
- Position tracking (`Vector2`)
- Pure virtual `Render()` and `Update()` methods
- Virtual destructor for proper inheritance

#### Ball Class

_Physics-driven game element_ with:
- Configurable radius and color
- Velocity-based movement
- Collision detection with paddles
- Sound effects for wall/paddle impacts

_Implementation in_ `Ball.cpp` handles:
- Rendering as a circle
- Position updates based on frame time
- Boundary collision responses
- Score tracking when passing paddles

#### Player Classes

##### Player1

_Controlled by W/S keys:_
- Rectangular paddle (`15x200` pixels)
- Vertical movement constraints within screen bounds
- Movement speed of `400` pixels/second

##### Player2

Extends `Player1` with mode selection:
- `"USER"` mode: Controlled by UP/DOWN arrow keys
- `"AI"` mode: Automated tracking of ball position
- Same physical properties as `Player1`

_Implementation in_ `Player1.cpp` and `Player2.cpp`

### Scene Management

_Defined in_ `Manager.h` and `Scenes.h`

#### Scene Base Class

Interface for all scenes with:
- Pure virtual `Render()` and `Update()` methods
- Virtual destructor

#### SceneManager

Scene stack manager supporting:
- Scene transitions with `ChangeScene()`
- Scene suspension for pausing
- Memory management with smart pointers
- Batch processing of scene changes

_Implementation in_ `Manager.cpp`

#### Implemented Scenes

##### MainMenu

Initial interface with:
- Mode selection buttons (`1 Player`, `2 Player`)
- Exit option
- Visual assets and background music
- Game state initialization

##### Play

Active gameplay scene containing:
- Ball entity with physics
- Both player paddles
- Real-time score display
- Pause functionality (**ESC** key)

_Implementation in_ `Play.cpp`

##### PauseMenu

In-game menu with:
- Resume gameplay option
- Return to main menu
- Exit application

_Implementation in_ `PauseMenu.cpp`

### UI Elements

_Defined in_ `ELement.h` 

#### Element Base Class

Foundation for interactive components with:
- Position tracking
- Pure virtual `Render()`/`Update()` methods
- Virtual destructor

#### Button

Interactive UI component with:
- Text labels
- Mouse hover detection
- Click callbacks
- Audio feedback (hover/click sounds)

_Implementation in_ `Button.cpp`

## Game Mechanics

### Controls

**Player 1** _(Left Paddle)_:
- Move Up: **W** key
- Move Down: **S** key

**Player 2** _(Right Paddle)_:
- Move Up: **UP** arrow key
- Move Down: **DOWN** arrow key

**General Controls**:
- Pause/Resume: **ESC** key

### Game Modes

1. **Single Player:** Compete against AI opponent
2. **Two Player:** Local multiplayer on same keyboard

Mode selection occurs in the `MainMenu` scene.

### Scoring System

- Points awarded when opponent misses ball
- Score displayed at top center of screen
- Game continues indefinitely (no explicit win condition)

## Technical Implementation

### Dependencies

- **Raylib** graphics and audio library
- **C++17** standard library
  - Smart pointers for memory management
  - Standard containers (`vector`)
  - Functional programming (`std::function`)

### Audio System

_Raylib-powered sound implementation:_
- WAV format support
- Per-button hover and click effects
- Collision sound effects with pitch/volume control
- Background music in menu scenes

Sounds loaded from `Assets/Sounds/` directory.

### Graphics Rendering

_Visual implementation using Raylib primitives:_
- Solid white background
- Black game elements for contrast
- Dynamic positioning based on window dimensions
- Text rendering for UI and scores
- Frame-rate independent movement

## Build and Execution

### Prerequisites

- C++ compiler with **C++17** support
- **Raylib** library (v4.0+ recommended)
- Windows/macOS/Linux development environment

### Compilation

_Typical build process:_
1. Link Raylib library during compilation
2. Compile all `.cpp` source files
3. Ensure asset paths are correctly configured

### Running the Game

_Execute the compiled binary to:_
1. Access main menu
2. Select game mode
3. Begin playing with keyboard controls
4. Pause anytime with **ESC** key
