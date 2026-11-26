# PathFinding

**WARNING: this project is not finished yet** --installation, compilation and usage may be tedious (daily commits and updates)

A real-time, interactive pathfinding visualizer written in **C** using **SDL3** and **SDL3_ttf**. It lets you draw obstacles on a grid, choose between Breadth-First Search (BFS) and A* Search, and watch the selected algorithm explore the grid and reconstruct a route from a randomly placed start cell to a destination.

## Table of contents

- [Overview](#overview)
- [Features](#features)
- [Algorithms](#algorithms)
- [Controls](#controls)
- [Grid legend](#grid-legend)
- [Requirements](#requirements)
- [Get the source code](#get-the-source-code)
- [Build](#build)
  - [Windows](#windows)
  - [macOS](#macos)
  - [Linux](#linux)
- [Run](#run)
- [Project structure](#project-structure)
- [Configuration](#configuration)
- [Known limitations and notes](#known-limitations-and-notes)
- [Technologies](#technologies)

## Overview

The application displays a grid containing a start point, an end point, and optional walls. You can edit the maze with the mouse and launch a search algorithm with the keyboard.

While the algorithm runs, the application updates the grid in real time. Explored cells are marked as visited; if a route is found, the cells belonging to that route are highlighted. A counter displays the number of steps recorded by the implementation.

The grid dimensions are currently fixed at **112 columns × 70 rows**. The application creates a fullscreen SDL window and scales the grid cells to the display size.

## Features

- **Two pathfinding algorithms:** BFS and A*.
- **Interactive obstacle editing:** draw and erase walls directly on the grid.
- **Randomized endpoints:** generate new start and destination positions.
- **Live visualization:** see explored cells and the final route as the algorithm progresses.
- **Step counter:** monitor the number of steps recorded during the search.
- **Fullscreen rendering:** the grid is scaled to the current display dimensions.
- **Diagonal movement in A*:** A* considers horizontal, vertical, and diagonal neighbours, with a higher movement cost for diagonal moves.
- **Diagonal corner restriction:** diagonal movement is rejected when both adjacent orthogonal cells are walls.

## Algorithms

### Breadth-First Search (BFS)

BFS explores the grid in breadth-first order using a FIFO queue. In this implementation it checks the four orthogonal neighbours (left, right, up, and down).

Because every BFS move has the same cost, BFS finds a path with the fewest moves when a path exists. It does not use diagonal movement.

### A* Search

A* uses a min-priority queue (implemented as a binary heap) to select the next cell based on:

- `g`: the accumulated cost from the start cell;
- `h`: the heuristic estimate from the current cell to the destination;
- `f = g + h`: the priority used by the queue.

A* checks eight neighbours, including diagonals. Orthogonal moves cost `1`, while diagonal moves cost approximately `sqrt(2)`.

**Implementation note:** the current heuristic is Manhattan distance (`|dx| + |dy|`), while diagonal moves are enabled. This heuristic is not necessarily admissible for that movement model, so the current implementation should be treated as a visualization of A*, not as a guarantee of an optimal-cost path in every map.

## Controls

| Input | Action |
|---|---|
| `A` | Switch between BFS and A* |
| `Enter` | Start the selected algorithm |
| `Space` | Randomize the start and end cells (only when no search is running) |
| `Left mouse button` (hold and drag) | Draw walls |
| `Right mouse button` (hold and drag) | Erase walls |
| `Backspace` | Remove all walls |
| Window close / quit event | Exit the application |

The search runs one update step at a time, with the delay configured by `STEP_DELAY` in `include/settings.h`.

## Grid legend

| Cell | Colour | Meaning |
|---|---|---|
| Start | Green | Search starting point |
| Destination | Red | Target cell |
| Wall | Light grey | Blocked cell |
| Visited | Purple | Cell explored by the algorithm |
| Path | Yellow | Reconstructed route |
| Empty | Dark blue | Walkable, unexplored cell |

## Requirements

The project uses:

- A C compiler with **C11** support:
  - GCC or Clang on Linux and macOS;
  - MSVC, MinGW-w64, or another CMake-compatible C compiler on Windows.
- **CMake 3.16 or newer**.
- **SDL3** development files.
- **SDL3_ttf** development files.
- The `Caskaydia.ttf` font file at runtime (see [Known limitations and notes](#known-limitations-and-notes)).

The CMake configuration uses SDL's CMake package targets:

```cmake
SDL3::SDL3
SDL3_ttf::SDL3_ttf
```

Make sure both libraries are installed in a location CMake can discover, or provide the appropriate package-prefix/toolchain configuration.

## Get the source code

Clone the repository:

```bash
git clone https://github.com/<YOUR-USERNAME>/<YOUR-REPOSITORY>.git
cd <YOUR-REPOSITORY>
```

Replace the URL with the actual GitHub repository URL.

Alternatively, download the repository as a ZIP archive from GitHub and extract it.

## Build

The commands below use an out-of-source build directory named `build`.

### Important: fix the CMake file name first

The project archive currently contains a file named `CmakeLists.txt`. CMake expects the exact name **`CMakeLists.txt`** (capital `M` and `L`), especially on case-sensitive filesystems such as Linux.

Rename it before configuring the project:

```bash
mv CmakeLists.txt CMakeLists.txt
```

Run this command from the project root. If the file in your checkout is already named `CMakeLists.txt`, no action is needed.

### Windows

One straightforward dependency setup uses Visual Studio Build Tools and [vcpkg](https://github.com/microsoft/vcpkg).

1. Install **Git**, **CMake 3.16+**, and Visual Studio 2022 (or Build Tools) with the *Desktop development with C++* workload. The project itself is C, but the workload provides the MSVC toolchain.
2. Install and bootstrap vcpkg:

   ```powershell
   git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
   cd C:\vcpkg
   .\bootstrap-vcpkg.bat
   ```

3. Install SDL3 and SDL3_ttf:

   ```powershell
   .\vcpkg.exe install sdl3:x64-windows sdl3-ttf:x64-windows
   ```

4. Return to the project directory and configure CMake. Adjust the vcpkg path if you installed it elsewhere:

   ```powershell
   cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows
   ```

5. Build:

   ```powershell
   cmake --build build --config Release
   ```

The executable is normally created at:

```text
build\Release\PathFinding.exe
```

The project's post-build CMake command is intended to copy the SDL3 and SDL3_ttf runtime DLLs next to the executable. If Windows reports a missing DLL at launch, check that the corresponding vcpkg runtime DLLs are available beside `PathFinding.exe` or on `PATH`.

You can also use MinGW-w64, but you must configure CMake with a matching compiler and make both SDL3 CMake packages discoverable to that toolchain.

### macOS

1. Install Apple's command-line developer tools:

   ```bash
   xcode-select --install
   ```

2. Install Homebrew if it is not already installed: <https://brew.sh/>.
3. Install CMake and the SDL3 libraries:

   ```bash
   brew install cmake sdl3 sdl3_ttf
   ```

4. From the project root, configure and build:

   ```bash
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
   cmake --build build --parallel
   ```

If CMake cannot locate SDL3 or SDL3_ttf, check where Homebrew installed the packages and pass their prefix to CMake, for example:

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH="$(brew --prefix)"
```

### Linux

Install a C11 compiler, CMake, SDL3, and SDL3_ttf using your distribution's package manager. SDL3 package availability and package names depend on the distribution and its release.

#### Ubuntu / Debian

On releases that provide the SDL3 development packages:

```bash
sudo apt update
sudo apt install build-essential cmake libsdl3-dev libsdl3-ttf-dev
```

If `apt` cannot find one or both SDL3 packages, use a newer distribution release or install SDL3 and SDL3_ttf from their official source repositories. Install both libraries with CMake package configuration files enabled, and ensure their installation prefix is visible to CMake.

#### Fedora

On Fedora releases that provide the SDL3 development packages, install the compiler, CMake, and SDL3 development packages using `dnf`. Package names can vary by release:

```bash
sudo dnf install gcc gcc-c++ make cmake SDL3-devel SDL3_ttf-devel
```

If those package names are unavailable, search the enabled repositories for the SDL3 and SDL3_ttf development packages, or build/install the libraries from their official source repositories.

#### Arch Linux / Manjaro

On systems where the packages are available in the enabled repositories:

```bash
sudo pacman -S --needed base-devel cmake sdl3 sdl3_ttf
```

#### openSUSE

Package names vary between openSUSE releases and repositories. Install `gcc`, `make`, `cmake`, and the SDL3 / SDL3_ttf development packages using `zypper`. If the SDL3 development packages are not available for your release, build and install them from their official source repositories.

#### Build on Linux (after installing dependencies)

From the project root:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

If SDL3 was installed to a custom prefix, pass it explicitly:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/path/to/sdl3/prefix
cmake --build build --parallel
```

The same CMake configure/build commands apply to other Linux distributions once the compiler, CMake, SDL3, and SDL3_ttf development packages are installed.

## Run

Run the executable from the project root (or make sure the required font file is in the process's working directory):

- **Windows:** `build\Release\PathFinding.exe`
- **Linux:** `./build/PathFinding`
- **macOS:** `./build/PathFinding`

If you are using a multi-configuration CMake generator on Windows, the executable may be under `build/Release/`. On single-configuration generators, it may be directly under `build/`.

## Project structure

```text
PathFinding/
├── CMakeLists.txt          # CMake build configuration
├── include/
│   ├── astar.h             # A* state and interface
│   ├── bfs.h               # BFS state and interface
│   ├── font.h              # SDL_ttf text helpers
│   ├── grid.h              # Grid types and grid operations
│   ├── input.h             # Mouse input helpers
│   ├── machine.h           # Main application state and loop interfaces
│   ├── priorityqueue.h     # A* priority queue declarations
│   ├── queue.h             # BFS FIFO queue declarations
│   └── settings.h          # Grid dimensions and constants
└── src/
    ├── astar.c             # A* implementation
    ├── bfs.c               # BFS implementation
    ├── font.c              # Font and text rendering
    ├── grid.c              # Grid initialization, drawing, and movement checks
    ├── input.c             # Wall drawing and erasing
    ├── machine.c           # SDL setup, events, updates, and rendering
    ├── main.c              # Program entry point
    ├── priorityqueue.c     # Binary min-heap implementation
    └── queue.c             # FIFO queue implementation
```

## Configuration

The main compile-time settings are in `include/settings.h`:

| Constant | Current value | Purpose |
|---|---:|---|
| `COLS` | `112` | Number of grid columns |
| `ROWS` | `70` | Number of grid rows |
| `STEP_DELAY` | `1` | Minimum delay, in milliseconds, between algorithm updates |

Change these values and rebuild to experiment with different grid sizes or visualization speed. The queue and priority-queue storage sizes are based on `ROWS * COLS`, so keep the data structures' capacity assumptions in mind when changing the grid dimensions.

## Known limitations and notes

- **CMake filename casing:** the supplied archive uses `CmakeLists.txt`; rename it to `CMakeLists.txt` before building on systems where filename case matters. Ideally, commit the correctly named file to the repository.
- **Fullscreen mode:** the window is created with `SDL_WINDOW_FULLSCREEN`; there is currently no windowed-mode setting exposed in the controls.
- **BFS and A* use different movement rules:** BFS checks four directions, while A* checks eight (since BFS does not know the difference between diagonal and straight, the relult would be terrible).
- **A* heuristic:** the current Manhattan heuristic is paired with diagonal movement. As noted above, this means optimality is not guaranteed for all maps (better visualization purposes).
- **Search lifecycle:** the current controls do not expose a dedicated cancel/reset-search command. Restarting a search is gated while an algorithm is running; use the application as currently implemented.
- **Dependency discovery:** CMake expects SDL3 and SDL3_ttf to provide their CMake config packages and imported targets. Installing only runtime libraries is not sufficient; development packages are required.

## Technologies

- **C** — application and pathfinding implementations.
- **CMake** — cross-platform build configuration.
- **SDL3** — window creation, input handling, rendering, and timing.
- **SDL3_ttf** — font loading and text rendering.

---

If you find a bug or have an idea for an improvement, feel free to open an issue or submit a pull request.
