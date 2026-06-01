# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

*Echoes of the Sol Frontier* — a 2D tile-based real-time space sandbox (single-player, Windows, C++). Game design notes live in `C:\Projects\echoes\!docs\` (`game_description.md`, `design_document.md`, `lore.md`).

## Build

The solution is `C:\Projects\echoes\AllodsApp\AllodsApp.sln` and pulls in three sibling library projects from `C:\Projects\echoes\`: `LaggySdk` (foundation: vectors, events, serialization, contracts), `LaggyDx` (engine: DirectX-based 2D renderer, sprites, controls, camera, animation, thermodynamics `Dx::thd`), and `DirectXTK`.

Build from the AllodsApp directory:

```
MSBuild.exe AllodsApp.sln -p:Configuration=Debug -p:Platform=x64 -m -nologo -v:m
```

Only `x64` is wired up — the ARM64 / x86 entries in the .sln redirect to x64/Win32 stubs. Output: `AllodsApp/bin/AllodsApp.exe`. Runtime expects `bin/Data/` (Assets, Configs) and writes saves to `bin/Saves/`. There is no test suite.

## Architecture

### Layers and dependency direction

`AllodsApp` (game) → `LaggyDx` (engine, namespace `Dx`) → `LaggySdk` (namespace `Sdk`). The game subclasses `Dx::App` (`Game`). Engine APIs are abstract (`Dx::ISpriteShader`, `Dx::ICamera2`, `Dx::ITexture`, `Dx::IControl`) — game code consumes interfaces, not concretes.

### Coordinate systems (important)

- `TileCoord` = `Sdk::Vector2I` (alias in `Fwd.h`) — discrete tile grid, always integer.
- World/absolute positions and the rendering pipeline are `Sdk::Vector2F` (floats). `FreeBaseEntity::d_position` (base of `Object`, `Avatar`) is `Vector2F`.
- Texture/sprite sizes are integer pixels (`frameSize`, `Sdk::Vector2I`). `FreeBaseEntity::getSize()` returns int; `getRect()` returns `Sdk::RectI` and casts position to int at that boundary.
- `Sdk::Vector2<T>` has **no implicit conversion** between `int` and `float` — explicit `getVector<float>()` / `getVector<int>()` at boundaries (e.g. cursor position is `Vector2I`, must be converted before passing to `TileUtils::getTileCoords`).
- `Constants::TileSize` is `int`. When used in `Vector2F` initializer lists, cast explicitly: `{ (float)(coord.x * Constants::TileSize), ... }`.

### Game object model

- `Entity` (base, in `Entity.h`) — has a `Prototype`, animation player, `IBehaviorModel`, mass/temperature, implements `Sdk::ISerializable` and `Dx::thd::IThdObject` (thermodynamics).
- `FreeBaseEntity` extends `Entity` with a float `Vector2F` position. `Object`, `Avatar` derive from it.
- `TileBaseEntity` extends `Entity` for grid-locked things. `Structure` derives from it.
- `Mount` is a fixture-attached entity (lamps, switches) — positioned via `MountUtils` relative to its host `Structure`'s `Fixture`.
- `Tile` owns: a `LayersMap` (`Layer::Panneling`/`Floor`/`Wall`/`Furniture` → `StructurePtr`), free `Objects` and `Avatars`, and a `GasThd` unit for atmospheric simulation.
- `Location` owns the `Tiles` map keyed by `TileCoord`. `Session` owns the current `Location`, camera, `BuildManager`, `InteractionManager`, optional `IOverlay`.

### Behavior models

Entities can carry a `BehaviorModel` (`IBehaviorModel`) — examples: `DoorBehavior`, `LampBehavior`, `GasTankBehavior`, `ContainerBehavior`. Behavior is selected from `Prototype::bahaviorModel` enum at construction.

### Prototypes and data

`Prototype` (and subtypes `StructurePrototype` / `MountPrototype` / `ObjectPrototype` / `AvatarPrototype`) are loaded from `bin/Data/Configs/` by `PrototypeLoader` into `PrototypesCollection`. Gameplay code looks entities up by `PrototypeName` (a `std::string`).

### Serialization

`Sdk::ISerializable` with `pushFields()` declares fields by name; `onFieldNotFound` handles legacy/optional fields, `onDeserialized` runs post-load fixups. `Vector2<T>::operator<</>>` writes raw `T`s — changing a `pushField`'ed type (e.g. `Vector2I` → `Vector2F`) silently changes save format and breaks existing saves.

### Rendering pipeline

`ViewController` drives per-frame rendering via `Dx::ISpriteShader`. The render order is: `BackgroundView` → for each tile `TileView` (which delegates to `StructureView` and `MountView`) → `ObjectView` for free objects → `AvatarView` → `OverlayView` (if any) → `BuildModeView` (build preview).

All `*View::render()` calls take `Vector2F` positions. `setPosition` on `Dx::Sprite`/`AnimatedSprite` is `Vector2F`. `ICamera2::getOffset()` is `Vector2F`; `IRenderDevice::getResolution()` and `Dx::CursorUtils::getPosition()` are `Vector2I` (convert at the call site).

### Input and build mode

`Game::onMouseClick` and `Game::onMouseRelease` both return `bool` (engine convention: consumed → true). Mouse events flow `Game` → `Session` → `BuildManager` / `InteractionManager`. `BuildManager` owns the in-flight `BuildDraftInfo` (a polymorphic struct: `BuildDraftInfo`, `BuildMountDraftInfo`, `BuildObjectDraftInfo`) that `BuildModeView` reads to render the preview.

### Events

`Sdk::EventHandler` is the in-process pub/sub spine. Subsystems `connectTo()` each other and dispatch `Sdk::IEvent` subclasses (`SessionAttachedEvent`, `LocationAddedEvent`, `BuildDraftSetEvent`, `OverlaySetEvent`, …). `processEvent` does `dynamic_cast` chains.

## Conventions

- Naming: members `d_foo`, parameters `i_foo` / `o_foo` / `io_foo`, types `PascalCase`, methods `camelCase`. `SAFE_DEREF(ptr)` dereferences with a contract check; `CONTRACT_EXPECT` / `CONTRACT_ASSERT` / `CONTRACT_ENSURE` / `CONTRACT_THROW` (from `LaggySdk/Contracts.h`) are the standard precondition/postcondition macros.
- Headers use `#pragma once` and forward-declare via `Fwd.h` aliases (`ObjectPtr`, `AvatarPtr`, `Objects`, `TileCoord`, …) rather than including each other.
- Commit message prefixes (visible in `git log`): `(+)` add, `(-)` fix/remove, `(*)` change, `(~)` refactor/cleanup.

## Gotchas

- C++20 features in use (designated initializers, `std::ranges`, concepts).
- `Vector2` lacks `Vector2I + Vector2F` mixed arithmetic — always convert one side.
- Texture `frameSize` is always int; if you compute `sprite.getSize() / 2` after a float migration, remember the result is float.
- The `pushField` serialization format is positional — renaming or retyping a field breaks existing saves in `bin/Saves/`.
