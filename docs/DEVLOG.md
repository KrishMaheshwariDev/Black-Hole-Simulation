# Day - 1

Tasks Completed:
- Integrating SOGL framework
- Modifying the SOGL files for path compatiblity
- Initialization of the git version system
- Cmake Configuration and CMakeList.txt works for now (i am cooked)
- clangd configuration is set
- Tested basic main.cpp program to ensure CMake and clangd works properly

Pushed Work :
- the project structure with libs and SOGL
- .gitignore is ready and won't cause problem for now
---
# Day - 2

Tasks Completed:

- Redesigned Mesh system from raw pointer-based arrays to modern C++ structures
- Created `StaticVertex` structure using `glm::vec`
- Separated CPU-side geometry (`MeshData`) from GPU-side rendering (`Mesh`)
- Implemented modern vertex/index container workflow using `std::vector`
- Added move constructor support for efficient geometry transfer
- Created `VertexLayout` system for centralized vertex attribute configuration
- Implemented VAO/VBO/EBO upload pipeline through `Mesh`
- Added procedural circle generation for rendering pipeline testing
- Created minimal vertex and fragment shaders for validation
- Implemented rendering flow through `Renderer::Draw(mesh, shader)`
- Successfully rendered generated circle in 800x800 window
- Refactored `main.cpp` to match new rendering architecture
- Cleaned include structure and removed temporary experimental code

Pushed Work :

- New rendering architecture foundation
- `VertexTypes`
- `MeshData`
- `Mesh`
- `VertexLayout`
- Procedural geometry generation system
- Basic shader assets
- Updated rendering pipeline using modern abstractions

Notes:

- Current rendering pipeline:

```
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

- Renderer architecture is now significantly cleaner and easier to extend later
- Future systems like model loading, PBR, animation, and Vulkan backend migration are now structurally possible without rewriting core mesh systems
- OpenGL still behaves like a state-machine cryptid from 1992, but the pipeline survived today

---
# Day - 3

Tasks Completed:
- Finalized rendering architecture for V1 black hole simulation
- Defined rendering responsibilities and separation between geometry and simulation
- Designed CircleMesh API
- Studied mathematical representation of circles and circle generation algorithms
- Implemented indexed circle mesh generation using triangle fan topology
- Integrated CircleMesh with SOGL MeshData and Mesh pipeline
- Added support for configurable radius and segment count
- Generated circle vertices using trigonometric parametrization
- Generated index buffer for closed circle topology
- Successfully rendered and validated:
  - Triangle (3 segments)
  - Square (4 segments)
  - Circle approximation (64 segments)
- Verified vertex layout compatibility with SOGL framework
- Completed first custom renderable object outside of SOGL

Challenges Faced:
- Mesh construction dependency on MeshData initialization
- Designing reusable geometry separate from simulation objects
- Understanding indexed mesh topology and circle closure logic
- Adapting circle generation to SOGL's triangle-only rendering pipeline

Key Learnings:
- OpenGL does not provide circles as primitives; circles are approximated using generated vertices
- Circle points can be generated using:
  x = r * cos(θ)
  y = r * sin(θ)
- Indexed meshes reduce duplicated vertices and improve geometry reuse
- Geometry, rendering, and simulation should remain independent systems
- SOGL Mesh abstraction currently supports triangle-based rendering only

Project Status:
- CircleMesh implementation complete and tested
- Rendering foundation established
- Ready to design Black Hole render object and particle rendering system