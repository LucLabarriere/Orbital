# Orbital Engine

Orbital is the basis of a Game engine using C++ and OpenGL (uses Glad, GLFW and GLM as external libraries) supported on Linux and Windows (as well as WSL).

## Features
- ECS (OK)
- 2D Renderer (OK)
- C++ Scripts (OK)
- Hot reloading scripts (OK, press `<F2>` to reload the scripts)
- 3D Renderer (planned)
- Physics Engine (planned)
- Imgui Debug layer (planned)
- Sound (planned)
- Serialization (planned)

## Requirements
Tested on Linux with G++ 11.2.0, 12.1.0 and CLang 15, and on Windows with G++ 11, CLang 15 and MSVC 19.32.
It requires at least OpenGL version 4.5 for now and CMake >=3.21.0

## Build
CMake is configured so that the binaries are exported to the `bin/` folder. This is required to allow the hot reloading of C++ scripts
