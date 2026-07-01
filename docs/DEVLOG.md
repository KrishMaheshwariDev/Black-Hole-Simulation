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
---
# Day - 5

## Objectives
- Introduce a reusable transform system
- Support per-object runtime positioning through model matrices
- Remove origin-locked rendering behavior from simulation objects

---

## Tasks Completed

### Transform System
- Added `Transform` fields for `position`, `rotation`, and `scale`
- Implemented `Transform::GetMatrix()` using GLM
- Established model-matrix generation for renderable simulation objects

### Rendering Integration
- Added `uModel` support to the rendering pipeline
- Updated the vertex shader to apply `uProjection * uModel`
- Refactored `CircleMesh` draw flow to accept an external `Transform`

### Runtime Object Control
- Separated geometry from per-instance transform state
- Enabled compile-time initialization of object transforms in `main.cpp`
- Enabled runtime transform mutation for future simulation-driven updates

---

## Architecture Decisions

### Object Rendering Flow

```text
Local Mesh Geometry
        ↓
   Transform
        ↓
   Model Matrix
        ↓
  Projection Matrix
        ↓
     Screen
```

### Simulation Ownership Model

```text
Geometry
    ↓
Entity Owns Transform
    ↓
Simulation Updates Transform
    ↓
Renderer Draws Latest State
```

---

## Key Learnings

- Geometry should stay authored in local space while transforms define world placement.
- Object transforms should not be embedded inside reusable mesh generators.
- Model matrices create a clean handoff between simulation state and rendering state.

---

## Challenges Faced

- Avoiding hard-coded object positions inside render objects.
- Designing a transform flow that works both at startup and during runtime updates.
- Preserving the earlier rendering abstraction while introducing per-instance state.

---

## Project Status

The project now supports dynamic object placement through a dedicated transform system, which prepares the simulation layer for true per-entity motion.

Current Progress:

```text
[✓] Rendering Framework
[✓] Mesh Architecture
[✓] CircleMesh
[✓] Shader Pipeline
[✓] FPS Monitoring
[✓] Orthographic Projection
[✓] Transform System
[ ] Black Hole Entity
[ ] Physics System
[ ] Particle System
```

---

## Next Steps

1. Create simulation entities that own geometry, transform, and physics
2. Build a fixed-timestep global physics update loop
3. Separate render updates from physics updates
4. Introduce particle-specific simulation objects

---
# Day - 6

## Objectives
- Introduce proper simulation entities
- Build a global fixed-timestep physics update path
- Prepare the simulation architecture for future systems such as gravity

---

## Tasks Completed

### Entity System
- Refactored `Planet` to own geometry, transform, and physics body
- Refactored `BlackHole` to own geometry, transform, and physics body
- Added dedicated `LightParticle` simulation entity

### Physics Foundation
- Extended `PhysicsBody` with accumulated force support
- Added acceleration calculation from force and mass
- Added force clearing and static-body handling
- Created `PhysicsSystem` as a step-based global simulation updater

### World Organization
- Added `SimulationWorld` container to own global simulation state
- Integrated `FixedTimestep` into `main.cpp` at `20 TPS`
- Separated physics ticking from render-frame drawing

---

## Architecture Decisions

### Entity Composition

```text
Entity
 ├── Geometry
 ├── Transform
 └── PhysicsBody
```

### Physics Update Flow

```text
Fixed Timestep
      ↓
 PhysicsSystem
      ↓
  Physics Steps
      ↓
 Entity State Update
      ↓
 Renderer Draws Latest State
```

---

## Key Learnings

- A global simulation world simplifies cross-entity system updates.
- Step-based physics pipelines are easier to extend than single monolithic update functions.
- Decoupling render FPS from simulation TPS gives more predictable simulation behavior.

---

## Challenges Faced

- Making simulation entities own GPU-backed geometry safely.
- Preserving a simple architecture while creating room for future systems.
- Structuring physics in a way that supports gravity and additional update passes later.

---

## Project Status

The project now has a real simulation layer with entity ownership and a fixed-timestep physics pipeline, even though only basic integration is implemented so far.

Current Progress:

```text
[✓] Rendering Framework
[✓] Mesh Architecture
[✓] CircleMesh
[✓] Shader Pipeline
[✓] FPS Monitoring
[✓] Orthographic Projection
[✓] Transform System
[✓] Black Hole Entity
[✓] Planet Entity
[✓] Fixed Timestep Physics Loop
[ ] Gravity System
[ ] Particle Trail Rendering
```

---

## Next Steps

1. Improve light-particle rendering
2. Add visible particle trails for motion debugging
3. Introduce point-based light rendering instead of mesh-based rendering
4. Improve diagnostics for render and shader failures

---
# Day - 7

## Objectives
- Convert light particles into point-like light rays
- Add visible fading trails for motion visualization
- Extend the rendering layer with a particle-specific draw path

---

## Tasks Completed

### Particle Redesign
- Removed circle-mesh rendering from `LightParticle`
- Converted light particles into point-sized simulation objects
- Added per-particle color and point-size control

### Trail Rendering
- Added trail history tracking using `TrailPoint`
- Added trail aging and pruning logic
- Implemented fading trail rendering using alpha falloff
- Implemented point-size falloff across older trail samples

### Particle Rendering Pipeline
- Added `PointRenderer`
- Added dedicated particle vertex and fragment shaders
- Enabled point-size rendering and alpha blending for particles

---

## Architecture Decisions

### Light Particle Representation

```text
LightParticle
 ├── Transform
 ├── PhysicsBody
 ├── Point Size
 ├── Color
 └── Trail History
```

### Particle Rendering Flow

```text
LightParticle State
        ↓
 Recorded Trail Points
        ↓
 PointRenderer
        ↓
 Particle Shader
        ↓
 Fading Trail On Screen
```

---

## Key Learnings

- Light rays are better represented as points than as circular meshes for this simulation style.
- Trails are valuable not only visually, but also for debugging motion and system behavior.
- Dedicated render paths are justified when object classes differ fundamentally in representation.

---

## Challenges Faced

- Converting particles away from mesh-based rendering without disturbing the rest of the pipeline.
- Designing trail fading using only simple point rendering.
- Keeping particle rendering independent from the mesh shader path.

---

## Project Status

The simulation now includes visible, ray-like light particles with fading motion trails, giving the system its first dynamic particle visualization.

Current Progress:

```text
[✓] Rendering Framework
[✓] Mesh Architecture
[✓] CircleMesh
[✓] Shader Pipeline
[✓] FPS Monitoring
[✓] Orthographic Projection
[✓] Transform System
[✓] Black Hole Entity
[✓] Planet Entity
[✓] Fixed Timestep Physics Loop
[✓] Light Particle Representation
[✓] Fading Trail Rendering
[ ] Gravity System
[ ] Diagnostics Module
```

---

## Next Steps

1. Improve runtime diagnostics
2. Add centralized logging
3. Track OpenGL state and shader issues more reliably
4. Fix render-state interactions between mesh rendering and particle rendering

---
# Day - 8

## Objectives
- Introduce centralized runtime logging
- Diagnose silent rendering failures in the updated render pipeline
- Fix interaction bugs between particle rendering and mesh rendering

---

## Tasks Completed

### Logging Infrastructure
- Added a shared `Logger` module
- Added centralized `Info`, `Warn`, and `Error` logging helpers
- Added OpenGL error polling through `Logger::LogOpenGLErrors`
- Reduced repeated console spam by suppressing duplicate warnings and errors

### Rendering Bug Investigation
- Diagnosed invalid OpenGL usage in buffer unbinding
- Fixed `Buffer::unbind()` to unbind using the correct target
- Diagnosed shader-state mismatch between mesh rendering and particle rendering
- Fixed projection uniform uploads so each shader is updated while bound

### Render Pipeline Stabilization
- Updated mesh draw flow to explicitly bind its shader before uploading model uniforms
- Improved shader uniform diagnostics, including missing `mat4` uniforms
- Preserved the particle rendering path while restoring black hole and planet rendering

---

## Architecture Decisions

### Diagnostic Flow

```text
Runtime Action
      ↓
 Logger
      ↓
 OpenGL Error Check
      ↓
 Console Output
```

### Multi-Shader Safety Model

```text
Bind Shader
    ↓
Upload Uniforms
    ↓
Issue Draw Call
    ↓
Validate OpenGL State
```

---

## Key Learnings

- OpenGL errors can remain queued and mislead later diagnostics if not isolated carefully.
- Silent state bugs are common when multiple shader programs share the same frame.
- Logging needs deduplication or it quickly becomes noise during render-loop failures.

---

## Challenges Faced

- Tracing the real source of `GL_INVALID_ENUM` through repeated downstream reports.
- Identifying that projection uploads were targeting the wrong active shader program.
- Improving diagnostics without overwhelming the console every frame.

---

## Project Status

The project now has a centralized diagnostics path and a corrected mixed-renderer pipeline, making both debugging and runtime stability much stronger.

Current Progress:

```text
[✓] Rendering Framework
[✓] Mesh Architecture
[✓] CircleMesh
[✓] Shader Pipeline
[✓] FPS Monitoring
[✓] Orthographic Projection
[✓] Transform System
[✓] Black Hole Entity
[✓] Planet Entity
[✓] Fixed Timestep Physics Loop
[✓] Light Particle Representation
[✓] Fading Trail Rendering
[✓] Logger Module
[✓] Render State Diagnostics
[ ] Gravity System
[ ] Orbital Dynamics
```

---

## Next Steps

1. Implement the gravity system as a new physics step
2. Apply gravitational force between black holes, planets, and light particles as needed
3. Validate stable orbital behavior at fixed timestep
4. Expand diagnostics as new physics systems are added
