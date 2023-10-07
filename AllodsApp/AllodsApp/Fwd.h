#pragma once

#include <LaggySdk/Vector.h>


class Game;
using PrototypeName = std::string;
class Session;
class Entity;
class Structure;
class Mount;
struct Prototype;
struct StructurePrototype;
struct MountPrototype;
using StructurePtr = std::shared_ptr<Structure>;
using MountPtr = std::shared_ptr<Mount>;
class Tile;
using TileCoord = Sdk::Vector2I;
class Location;
struct BuildDraftInfo;
class IBehaviorModel;
using BehaviorModelPtr = std::shared_ptr<IBehaviorModel>;
struct Scenario;
class IOverlay;
