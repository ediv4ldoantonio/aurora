# Aurora Engine

Aurora is a lightweight 2D game engine written in modern C++20.

The project is being developed from the ground up with a focus on understanding
the architecture and responsibilities of a game engine rather than relying on
a large existing engine framework.

The engine currently provides foundations for application lifecycle, window
management, input, events, ECS, scenes, entities, components, systems, asset
management, 2D rendering, textures, cameras, render commands, sprite
batching, and renderer API abstraction.

---

## Table of Contents

- [Project Goals](#project-goals)
- [Technology](#technology)
- [Project Structure](#project-structure)
- [Architecture](#architecture)
- [Application Flow](#application-flow)
- [ECS](#ecs)
- [Scene System](#scene-system)
- [System Architecture](#system-architecture)
- [Rendering Architecture](#rendering-architecture)
- [Sprite Batching](#sprite-batching)
- [Camera](#camera)
- [Assets](#assets)
- [Build](#build)
- [Development](#development)
- [Current Status](#current-status)
- [Roadmap](#roadmap)
- [Architecture Principles](#architecture-principles)
- [Development Philosophy](#development-philosophy)

---

# Project Goals

Aurora is primarily a learning and engineering project.

The main goals are:

1. Understand how a game engine is structured.
2. Build the major engine systems from first principles.
3. Maintain clear separation between engine subsystems.
4. Use modern C++20 practices.
5. Keep platform-specific code isolated.
6. Build abstractions that allow different rendering backends.
7. Understand how ECS, rendering, resources, scenes, and systems interact.
8. Gradually move toward a production-quality architecture.

The engine is developed incrementally. Each subsystem is introduced after
understanding its responsibilities and its interaction with the rest of the
engine.

---

# Technology

- **Language:** C++20
- **Build system:** CMake
- **Build generator:** Ninja
- **Compiler:** GCC
- **Platform:** Linux
- **Windowing / platform layer:** SDL

SDL is currently responsible for platform-level functionality such as window
creation, input, rendering, and textures.

---

# Project Structure

```text
Aurora/
├── Engine/
│   ├── Include/
│   │   └── Aurora/
│   │       ├── Assets/
│   │       ├── Core/
│   │       ├── ECS/
│   │       ├── Events/
│   │       ├── Input/
│   │       ├── Math/
│   │       ├── Renderer/
│   │       ├── Scene/
│   │       └── Systems/
│   │
│   └── Source/
│       ├── Assets/
│       ├── Core/
│       ├── ECS/
│       ├── Input/
│       ├── Math/
│       ├── Platform/
│       │   └── SDL/
│       ├── Renderer/
│       ├── Scene/
│       └── Systems/
│
├── ThirdParty/
├── CMakeLists.txt
└── README.md
```

## Include Structure

```text
Engine/Include/Aurora
├── Assets
│   ├── Asset.h
│   └── AssetManager.h
│
├── Core
│   ├── Application.h
│   ├── Layer.h
│   ├── LayerStack.h
│   ├── Logger.h
│   ├── Time.h
│   ├── UUID.h
│   └── Window.h
│
├── ECS
│   ├── Component.h
│   ├── ComponentPool.h
│   ├── Registry.h
│   ├── Registry.inl
│   ├── System.h
│   ├── SystemManager.h
│   ├── View.h
│   └── View.inl
│
├── Events
│   ├── ApplicationEvents.h
│   ├── EventDispatcher.h
│   ├── Event.h
│   ├── EventTypes.h
│   └── KeyEvents.h
│
├── Input
│   ├── Input.h
│   └── KeyCodes.h
│
├── Math
│   ├── Matrix4.h
│   ├── Transform.h
│   └── Vector2.h
│
├── Renderer
│   ├── Camera2D.h
│   ├── Color.h
│   ├── GraphicsContext.h
│   ├── Renderer2D.h
│   ├── RendererAPI.h
│   └── Texture2D.h
│
├── Scene
│   ├── Components
│   │   ├── Component.h
│   │   ├── IDComponent.h
│   │   ├── NameComponent.h
│   │   ├── RelationshipComponent.h
│   │   ├── ScriptableEntity.h
│   │   ├── ScriptComponent.h
│   │   ├── SpriteComponent.h
│   │   └── TransformComponent.h
│   ├── Entity.h
│   ├── Entity.inl
│   ├── Scene.h
│   └── Scene.inl
│
└── Systems
    ├── RenderSystem.h
    ├── ScriptSystem.h
    └── TransformSystem.h
```

---

# Architecture

Aurora is organized into several major layers:

```text
Application
    │
    ▼
Scene
    │
    ├── Registry
    │      │
    │      ├── Entities
    │      └── Components
    │
    └── SystemManager
           │
           ├── ScriptSystem
           ├── TransformSystem
           └── RenderSystem
                          │
                          ▼
                     Renderer2D
                          │
                          ▼
                    Render Commands
                          │
                          ▼
                     Sprite Batch
                          │
                          ▼
                     RendererAPI
                          │
                          ▼
                     SDL Backend
```

The architecture separates responsibilities between ECS, scene management,
systems, rendering, and platform-specific code.

---

# Application Flow

The engine follows a traditional game loop:

```text
Initialize
    │
    ▼
Application Loop
    │
    ├── Process Events
    ├── Update
    └── Render
    │
    ▼
Shutdown
```

The scene updates its systems using the frame delta time and then executes its
rendering systems.

Conceptually:

```cpp
scene.OnUpdate(dt);
scene.OnRender();
```

---

# ECS

Aurora uses an Entity Component System architecture.

The main ECS objects are:

```text
Registry
Entity
Component
ComponentPool
View
System
SystemManager
```

## Registry

The registry manages ECS state and is responsible for:

- Entity creation
- Entity destruction
- Component storage
- Component lookup
- Component removal
- Views

Component storage uses type-based pools:

```text
Registry
│
├── ComponentPool<TransformComponent>
├── ComponentPool<SpriteComponent>
├── ComponentPool<NameComponent>
├── ComponentPool<ScriptComponent>
└── ...
```

The pools are stored through `std::unique_ptr<IComponentPool>`, allowing
different component pool types to be stored behind a common interface.

## Entity

An `Entity` is a lightweight handle to an entity inside a scene.

Conceptually:

```text
Entity
 ├── EntityID
 ├── Registry*
 └── Scene*
```

The entity does not own its components. The registry owns the component data.

Typical operations include:

```cpp
entity.AddComponent<TransformComponent>();
entity.HasComponent<SpriteComponent>();
entity.GetComponent<SpriteComponent>();
entity.RemoveComponent<SpriteComponent>();
entity.Destroy();
```

---

# Components

Components primarily contain entity data.

Current scene components include:

```text
TransformComponent
SpriteComponent
NameComponent
IDComponent
RelationshipComponent
ScriptComponent
```

For example:

```cpp
struct TransformComponent : public Component
{
    Transform LocalTransform;
    Transform WorldTransform;
};
```

---

# Scene System

A `Scene` represents a world containing entities.

The scene coordinates:

```text
Scene
│
├── Registry
├── SystemManager
└── Scene-level operations
```

The registry owns ECS data while the system manager coordinates system
execution.

---

# System Architecture

Systems contain behavior that operates on components.

Current systems include:

```text
ScriptSystem
TransformSystem
RenderSystem
```

The system manager is responsible for updating and rendering the registered
systems.

Conceptually:

```cpp
system->OnUpdate(registry, dt);
system->OnRender(registry);
```

---

# Transform System

The transform system calculates world transforms from local transforms and
entity relationships.

A `Transform` contains:

```cpp
Vector2 Position;
float Rotation;
Vector2 Scale;
```

A `TransformComponent` contains:

```cpp
Transform LocalTransform;
Transform WorldTransform;
```

This separates local transforms from final world-space transforms.

---

# Rendering Architecture

Rendering is separated into multiple layers:

```text
RenderSystem
     ↓
Renderer2D
     ↓
SpriteDrawCommand
     ↓
Render Queue / Batch
     ↓
RendererAPI
     ↓
Platform Backend
```

The high-level renderer should not need to know the details of the underlying
graphics implementation.

---

# RendererAPI

`RendererAPI` defines the rendering operations required by the engine.

The current platform implementation is:

```text
RendererAPI
     │
     └── SDLRendererAPI
```

This abstraction makes it possible to introduce additional graphics backends
later without rewriting the high-level rendering system.

Potential future backends include OpenGL, Vulkan, or DirectX.

---

# Renderer2D

`Renderer2D` is the high-level 2D rendering layer.

Instead of immediately submitting every sprite to the platform renderer, it
creates render commands.

Conceptually:

```text
DrawSprite()
    ↓
SpriteDrawCommand
    ↓
Render Queue
    ↓
Sort
    ↓
Batch
    ↓
Flush
```

This separates render submission from render execution.

---

# SpriteDrawCommand

A sprite draw command contains the information necessary to render a sprite.

The command represents rendering data rather than ownership.

Conceptually it contains:

```text
Transform
Color
Texture
Layer / ordering information
```

The renderer uses these commands to construct the final rendering operations.

---

# Sprite Batching

Aurora uses sprite batching to reduce the number of rendering submissions.

A sprite contributes:

```text
4 vertices
6 indices
```

Multiple sprites can be accumulated into a single batch.

Conceptually:

```text
Sprite A ─┐
Sprite B ─┤
Sprite C ─┼──> Batch ──> RendererAPI
Sprite D ─┘
```

When the current batch cannot accept another sprite, the renderer flushes the
current batch and starts a new one.

This is called an automatic batch break.

---

# Texture Slots

Sprites can reference textures using texture slots.

The current convention reserves texture slot `0` for the absence of a
texture.

Conceptually:

```text
0 → no texture
1 → texture A
2 → texture B
3 → texture C
...
```

This allows vertices to reference a texture slot instead of storing an actual
texture object per vertex.

---

# Render Ordering

Sprites can be assigned a rendering layer.

For example:

```text
-10 → background
  0 → gameplay
 10 → foreground
100 → UI
```

The renderer can sort commands by their rendering layer before batching.

Stable ordering is important for sprites sharing the same layer because
submission order can affect the final image, especially when transparency is
involved.

---

# Camera

Aurora contains a `Camera2D` abstraction.

The camera stores a world-space position and provides world-to-screen
conversion.

Conceptually:

```text
World Position
      │
      ▼
Camera Transform
      │
      ▼
Screen Position
```

The camera is part of the rendering architecture, while the renderer API
remains independent of camera-specific logic.

---

# Math

Aurora contains foundational math types:

```text
Vector2
Transform
Matrix4
```

`Transform` currently contains:

```cpp
Vector2 Position;
float Rotation;
Vector2 Scale;
```

`Matrix4` provides the foundation for matrix-based transformations and future
projection support.

---

# Assets

Aurora contains an asset abstraction and asset manager:

```text
Asset
AssetManager
Texture2D
```

The intended ownership model is:

```text
AssetManager
     │
     └── owns assets

Renderer
     │
     └── references assets
```

Rendering code should not unexpectedly take ownership of resources.

---

# Scripts

Aurora contains the foundation for entity scripts:

```text
ScriptableEntity
ScriptComponent
ScriptSystem
```

The intended script lifecycle is:

```text
OnCreate
    ↓
OnUpdate
    ↓
OnDestroy
```

The script system is responsible for managing script execution and lifecycle.

---

# Entity Relationships

Entities support parent/child relationships through:

```text
RelationshipComponent
```

This provides the foundation for scene hierarchies such as:

```text
Player
├── Weapon
├── Camera
└── CharacterSprite
```

The transform system can use these relationships to calculate world
transforms from local transforms.

---

# Build

## Requirements

You need:

- C++20 compiler
- CMake
- Ninja
- SDL dependencies

The project is currently developed with GCC on Linux.

## Configure

From the project root:

```bash
cmake -S . -B build -G Ninja
```

## Build

```bash
cmake --build build
```

## Clean Build

```bash
rm -rf build
cmake -S . -B build -G Ninja
cmake --build build
```

---

# Development

The development workflow is intentionally incremental:

```text
Understand architecture
        ↓
Implement subsystem
        ↓
Compile
        ↓
Test
        ↓
Commit
        ↓
Move to next subsystem
```

Changes should generally remain focused.

Example:

```text
feat(renderer): add sprite batching
```

is preferable to combining unrelated engine changes into a single commit.

---

# Current Status

## Core

- [x] Application
- [x] Window
- [x] Layer stack
- [x] Logger
- [x] Time
- [x] UUID

## Events / Input

- [x] Event system
- [x] Event dispatcher
- [x] Application events
- [x] Keyboard events
- [x] Input abstraction

## ECS

- [x] Entity
- [x] Registry
- [x] Component storage
- [x] Component pools
- [x] Views
- [x] Systems
- [x] System manager
- [x] Entity destruction
- [x] Pending destruction

## Scene

- [x] Scene
- [x] Entity/scene relationship
- [x] Transform component
- [x] Sprite component
- [x] Name component
- [x] ID component
- [x] Relationship component
- [x] Script component
- [x] Scriptable entity

## Rendering

- [x] Renderer API abstraction
- [x] SDL renderer backend
- [x] Renderer2D
- [x] Sprite rendering
- [x] Texture rendering
- [x] Sprite draw commands
- [x] Render queue
- [x] Sprite batching
- [x] Texture slots
- [x] Batch limits
- [x] Automatic batch flushing
- [x] Render ordering
- [x] Camera2D foundation
- [x] Matrix4 foundation

## Assets

- [x] Asset abstraction
- [x] Asset manager
- [x] Texture resources

---

# Roadmap

## Rendering

- [ ] Material abstraction
- [ ] More advanced texture batching
- [ ] OpenGL renderer backend
- [ ] GPU vertex buffers
- [ ] Vertex arrays
- [ ] Index buffers
- [ ] Shaders
- [ ] Texture arrays / texture units
- [ ] Orthographic projection
- [ ] Proper camera matrices
- [ ] Render targets
- [ ] Framebuffers

## ECS

- [ ] Entity generation/versioning
- [ ] More efficient component storage
- [ ] Query improvements
- [ ] Improved relationship management

## Scene

- [ ] Scene serialization
- [ ] Scene loading
- [ ] Scene saving
- [ ] Prefabs
- [ ] Entity duplication
- [ ] Scene hierarchy improvements

## Assets

- [ ] Asset handles
- [ ] Asset lifetime management
- [ ] Asset caching improvements
- [ ] Async loading
- [ ] Asset serialization

## Input

- [ ] Mouse input
- [ ] Mouse buttons
- [ ] Controller support
- [ ] Input actions
- [ ] Input mapping

## Audio

- [ ] Audio abstraction
- [ ] Sound effects
- [ ] Music
- [ ] Audio resources
- [ ] Audio mixer

## Tools

- [ ] Debug renderer
- [ ] Editor
- [ ] Scene hierarchy
- [ ] Inspector
- [ ] Asset browser
- [ ] Entity editor

---

# Architecture Principles

## Separation of Responsibilities

Each subsystem should have a clear responsibility.

```text
Registry
    → ECS data

SystemManager
    → System execution

Renderer2D
    → High-level rendering

RendererAPI
    → Graphics backend abstraction

SDLRendererAPI
    → SDL implementation
```

## Explicit Ownership

Ownership should be represented explicitly.

For example:

```cpp
std::unique_ptr<T>
```

is used for exclusive ownership.

References and raw pointers are used where ownership is not transferred.

## Platform Isolation

SDL-specific implementation should remain inside:

```text
Engine/Source/Platform/SDL/
```

Engine-level code should depend on abstractions rather than SDL-specific
details whenever possible.

## Data and Behavior Separation

Components primarily represent data.

Systems operate on that data.

For example:

```text
TransformComponent
        ↓
TransformSystem
```

and:

```text
SpriteComponent
TransformComponent
        ↓
RenderSystem
        ↓
Renderer2D
```

## Correctness Before Optimization

The engine prioritizes correct architecture before optimization.

A typical progression is:

```text
Correct rendering
        ↓
Render ordering
        ↓
Batching
        ↓
Texture optimization
        ↓
GPU optimization
```

---

# Development Philosophy

Aurora is being built incrementally.

The objective is not only to make the engine work, but to understand why each
piece exists and how the pieces interact.

The intended progression is:

```text
Platform
   ↓
Core
   ↓
ECS
   ↓
Scene
   ↓
Systems
   ↓
Renderer abstraction
   ↓
2D renderer
   ↓
Batching
   ↓
GPU renderer
   ↓
Editor / tools
```

The architecture will evolve as new requirements are introduced.

---

# License

License information has not yet been defined.
