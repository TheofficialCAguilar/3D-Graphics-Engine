# 3D Graphics Engine

A fully custom 3D graphics engine built in C++ from scratch, developed across 6 progressive projects as part of a university graphics course. The engine implements core computer graphics concepts including real-time rendering, Phong lighting, a first-person camera, and a spatial data structure for scene management.

![OpenGL](https://img.shields.io/badge/OpenGL-4.1-blue) ![SDL2](https://img.shields.io/badge/SDL2-2.x-green) ![C++](https://img.shields.io/badge/C++-17-orange) ![Platform](https://img.shields.io/badge/Platform-macOS-lightgrey)

---

## Features

- **Real-time 3D rendering** via OpenGL 4.1 and GLSL shaders
- **Phong lighting model** — ambient, diffuse, and specular highlights with an orbiting light source
- **First-person camera** — WASD movement and mouse look
- **Texture mapping** — load any BMP texture onto geometry at runtime
- **OBJ mesh loader** — load custom 3D models exported from Blender or any 3D tool
- **Transform pipeline** — chain Scale, Translation, and Rotation operations via a linked list queue
- **Spatial BST** — Binary Search Tree organizing scene points by magnitude for frustum queries
- **Software PPM renderer** — fallback renderer that writes a `.ppm` image with no external dependencies

---

## Engine Architecture

The engine was built in 6 stages, each adding a new system:

| Project | System | Description |
|---------|--------|-------------|
| 1 | `Vector3D` | 3D math foundation — magnitude, normalization, operator overloads |
| 2 | `Rotation` | Euler, Axis-Angle, and Quaternion rotation representations |
| 3 | `RotationRegistry` | Array-based bag data structure storing and querying rotations |
| 4 | `Transformation` | Translation and Scale transforms with a CSV scene loader |
| 5 | `TransformPipeline` | Linked list queue chaining transforms — reverse, remove by type |
| 6 | `SpatialRegistry` | BST organizing Vector3D points by distance for spatial queries |

On top of this foundation the OpenGL layer adds:

- `Shader` — GLSL shader compilation and uniform management
- `Camera` — view and projection matrix generation using the Vector3D system
- `Mesh` — VAO/VBO GPU upload with positions, normals, and UV coordinates
- `Engine` — SDL2 game loop, input handling, and scene rendering

---

## Getting Started

### Prerequisites (macOS)
```bash
brew install sdl2 glew
```

### Build and Run
```bash
git clone https://github.com/TheofficialCAguilar/3d-graphics-engine.git
cd 3d-graphics-engine
make run
```

### Load a Custom 3D Model
```bash
./engine mymodel.obj
```

### Add a Texture
Drop any `.bmp` file in the project folder named `texture.bmp`, then press **T** in-game to toggle it.

---

## Controls

| Key | Action |
|-----|--------|
| `W / S` | Move forward / backward |
| `A / D` | Move left / right |
| `Q / E` | Move up / down |
| `Mouse` | Look around |
| `T` | Toggle texture on/off |
| `ESC` | Quit |

---

## Project Structure

```
3d-graphics-engine/
├── shaders/
│   ├── vertex.glsl       # GLSL vertex shader
│   └── fragment.glsl     # GLSL Phong lighting fragment shader
├── Engine.cpp            # Main game loop and scene
├── Shader.hpp/.cpp       # GLSL shader loader
├── Camera.hpp/.cpp       # First-person camera
├── Mesh.hpp/.cpp         # OBJ loader + GPU upload
├── Renderer.hpp/.cpp     # Software PPM renderer
├── Vector3D.hpp/.cpp     # 3D math (P1)
├── Rotation*.hpp/.cpp    # Rotation types (P2)
├── RotationRegistry      # ArrayBag of rotations (P3)
├── Translation/Scale     # Transform types (P4)
├── TransformPipeline     # Linked list pipeline (P5)
├── SpatialRegistry       # BST spatial index (P6)
└── Makefile
```

---

## Built With

- **C++17**
- **OpenGL 4.1** — GPU rendering pipeline
- **SDL2** — window management and input
- **GLEW** — OpenGL extension loading
- **GLSL** — vertex and fragment shaders

---

## Author

**Carlos Aguilar**  
[GitHub](https://github.com/TheofficialCAguilar)
