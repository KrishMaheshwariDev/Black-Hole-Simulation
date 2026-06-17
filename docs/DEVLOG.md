# Day - 1

## Objectives
- Establish the project foundation
- Configure the development environment
- Integrate the rendering framework into the project

---

## Tasks Completed

### Project Setup
- Integrated the SOGL framework
- Modified SOGL files for project path compatibility
- Created the initial project structure

### Development Environment
- Initialized Git version control
- Configured CMake build system
- Configured `clangd` for code intelligence and diagnostics

### Validation
- Created a minimal test application
- Verified CMake configuration and build process
- Confirmed `clangd` integration works correctly

---

## Key Learnings

- Proper project structure and tooling setup significantly reduce future development friction.
- Establishing build and tooling workflows early prevents integration issues later.
- A stable development environment is just as important as application code.

---

## Challenges Faced

- Resolving framework include path issues.
- Configuring CMake to correctly locate external dependencies.
- Ensuring build tooling and language server integration work together.

---

## Project Status

The development environment and project foundation are fully operational.

Current Progress:

```text
[✓] Git Repository
[✓] CMake Configuration
[✓] SOGL Integration
[✓] clangd Setup
[✓] Project Structure
[ ] Rendering Architecture
[ ] Simulation Systems
```

---

## Pushed Work

- Initial project structure
- SOGL integration
- `.gitignore` configuration
- CMake build system setup

---

## Next Steps

1. Design rendering architecture
2. Improve mesh abstraction layer
3. Create reusable geometry structures
4. Validate rendering pipeline

---
# Day - 2

## Objectives
- Modernize the rendering architecture
- Separate geometry generation from GPU rendering
- Establish reusable mesh abstractions

---

## Tasks Completed

### Rendering Architecture
- Redesigned mesh system from raw pointer-based arrays to modern C++ structures
- Separated CPU-side geometry (`MeshData`) from GPU-side rendering (`Mesh`)
- Implemented centralized rendering workflow

### Geometry System
- Created `StaticVertex` structure using `glm::vec`
- Implemented `MeshData` using `std::vector`
- Added move constructor support for efficient geometry transfer

### Vertex Management
- Created `VertexLayout` system
- Centralized vertex attribute configuration
- Standardized vertex buffer upload process

### GPU Pipeline
- Implemented VAO/VBO/EBO upload workflow
- Created rendering flow through `Renderer::Draw(mesh, shader)`
- Added minimal shader assets for validation

### Testing
- Implemented procedural circle generation
- Successfully rendered a generated circle
- Validated the complete rendering pipeline

---

## Architecture Decisions

### Rendering Pipeline

```text
MeshData
    ↓
Mesh
    ↓
Renderer
    ↓
Shader
    ↓
OpenGL
```

### System Separation

```text
CPU Geometry Generation
          ↓
      MeshData
          ↓
      GPU Upload
          ↓
        Mesh
          ↓
      Rendering
```

---

## Key Learnings

- CPU-side geometry and GPU-side rendering should remain independent.
- Modern container-based workflows are safer and easier to extend.
- Centralized vertex layouts eliminate duplicated OpenGL configuration code.
- Clean abstractions make future systems easier to integrate.

---

## Challenges Faced

- Migrating from raw memory management to modern containers.
- Designing reusable mesh abstractions without overengineering.
- Maintaining compatibility with the existing SOGL framework.

---

## Project Status

A clean rendering architecture is now established and ready for procedural geometry generation.

Current Progress:

```text
[✓] Rendering Foundation
[✓] MeshData
[✓] Mesh
[✓] VertexLayout
[✓] Shader Validation
[✓] Procedural Geometry Testing
[ ] Custom Render Objects
[ ] Simulation Systems
```

---

## Pushed Work

- New rendering architecture foundation
- `VertexTypes`
- `MeshData`
- `Mesh`
- `VertexLayout`
- Procedural geometry generation system
- Basic shader assets
- Updated rendering pipeline

---

## Next Steps

1. Design CircleMesh abstraction
2. Implement procedural circle generation
3. Validate indexed mesh rendering
4. Begin simulation-oriented rendering objects
---
# Day - 3

## Objectives
- Create the first reusable renderable object
- Implement procedural circle generation
- Finalize the rendering foundation for simulation objects

---

## Tasks Completed

### Rendering Design
- Finalized rendering architecture for the V1 simulation
- Defined separation between rendering and simulation systems
- Designed the `CircleMesh` API

### Mathematical Foundation
- Studied circle parametrization
- Explored procedural geometry generation techniques
- Derived vertex generation using trigonometric functions

### CircleMesh Implementation
- Implemented indexed circle generation
- Added configurable radius support
- Added configurable segment count support
- Generated vertex buffers using angular parametrization
- Generated index buffers for triangle fan topology

### Validation
- Successfully rendered:
  - Triangle (3 segments)
  - Square (4 segments)
  - Circle approximation (64 segments)
- Verified compatibility with SOGL mesh pipeline
- Validated vertex layout integration

---

## Architecture Decisions

### Circle Generation

```text
Angle θ
    ↓
cos(θ), sin(θ)
    ↓
Vertex Position
    ↓
MeshData
    ↓
Mesh
    ↓
Renderer
```

### Geometry Separation

```text
CircleMesh
    ↓
Generates Geometry
    ↓
MeshData
    ↓
Uploaded To GPU
    ↓
Rendered By Renderer
```

---

## Key Learnings

- OpenGL does not provide circles as primitive shapes.
- Circles are approximated using generated vertices.
- Circle vertices can be generated using:

```cpp
x = r * cos(theta);
y = r * sin(theta);
```

- Indexed meshes improve geometry reuse and reduce duplication.
- Rendering systems should remain independent from simulation logic.

---

## Challenges Faced

- Designing reusable geometry independent of simulation entities.
- Understanding indexed mesh topology.
- Correctly closing the circle while maintaining valid triangle connectivity.
- Adapting circle generation to SOGL's triangle-based rendering pipeline.

---

## Project Status

The first custom renderable object is complete and fully integrated into the rendering framework.

Current Progress:

```text
[✓] Rendering Foundation
[✓] Mesh Architecture
[✓] Vertex Layout System
[✓] CircleMesh
[✓] Indexed Rendering
[✓] Geometry Generation
[ ] Projection System
[ ] Transform System
[ ] Black Hole Entity
[ ] Gravity System
```

---

## Next Steps

1. Improve rendering robustness
2. Add FPS monitoring
3. Implement orthographic projection
4. Support dynamic window resizing
5. Begin Black Hole rendering object design

---
# Day - 4

## Objectives
- Improve development-time diagnostics
- Make rendering resolution independent
- Prepare the rendering pipeline for future simulation systems

---

## Tasks Completed

### Performance Monitoring
- Implemented FPS monitoring system
- Added real-time FPS display in the window title
- Refactored and cleaned `main.cpp`

### Rendering Improvements
- Investigated aspect ratio distortion during window resizing
- Designed the initial projection pipeline
- Implemented orthographic projection matrix generation using GLM
- Added dynamic viewport updates based on framebuffer size
- Integrated projection matrix uniforms into the shader pipeline
- Updated vertex shader to support projection transformations
- Fixed rendering stretch and squash issues during window resizing
- Added protection against minimized window edge cases (`height == 0`)

### Architecture Planning
- Defined the projection system architecture
- Evaluated future camera system requirements
- Established rendering roadmap for future simulation features

---

## Architecture Decisions

### Current Rendering Pipeline

```text
World Space
    ↓
Projection Matrix
    ↓
Clip Space
    ↓
Screen Space
```

### Camera Roadmap

```text
V1
 ├── Orthographic Projection
 ├── Black Hole Physics
 ├── Gravity System
 ├── Particle System
 └── Stable Rendering

V2
 ├── Camera2D
 ├── Zoom
 ├── Pan
 ├── Debug Overlay
 └── Text Rendering

V3
 ├── Perspective Projection
 ├── Camera3D
 └── Full 3D Simulation
```

---

## Key Learnings

- Rendering directly in NDC coordinates causes visible distortion when the window aspect ratio changes.
- An orthographic projection matrix provides resolution-independent rendering.
- Projection should be introduced before implementing any camera system.
- Camera abstraction is currently unnecessary for the scope of the V1 simulation.

---

## Challenges Faced

- Determining the correct location for projection logic without modifying SOGL.
- Maintaining visual correctness across arbitrary window dimensions.
- Planning future camera support without introducing premature abstractions.

---

## Testing

### Projection Validation
- Tested multiple window aspect ratios.
- Verified circles remain circular after resizing.
- Confirmed viewport updates correctly with framebuffer size changes.

### Stability Validation
- Verified FPS counter updates correctly.
- Confirmed minimized-window edge cases do not cause projection failures.

---

## Project Status

The rendering layer is now resolution independent and capable of maintaining correct geometry regardless of window size. The foundational rendering infrastructure is complete and ready to support simulation-specific systems.

Current Progress:

```text
[✓] Rendering Framework
[✓] Mesh Architecture
[✓] CircleMesh
[✓] Shader Pipeline
[✓] FPS Monitoring
[✓] Orthographic Projection
[ ] Transform System
[ ] Black Hole Entity
[ ] Gravity System
[ ] Euler Integration
[ ] Particle System
```

---

## Next Steps

1. Implement Transform system (`position`, `rotation`, `scale`)
2. Add model matrix support to the rendering pipeline
3. Create reusable renderable simulation objects
4. Implement `BlackHole`
5. Implement `GravitySystem`
6. Integrate Euler-based physics updates