#pragma once

#include <LaggySdk/Vector.h>


class Entity;
class Fixture;
class Game;
class IBehaviorModel;
class IOverlay;
class Location;
class Mount;
class Session;
class Structure;
class Tile;

struct BuildDraftInfo;
struct MountPrototype;
struct Prototype;
struct Scenario;
struct StructurePrototype;

using BehaviorModelPtr = std::shared_ptr<IBehaviorModel>;
using FixturePtr = std::shared_ptr<Fixture>;
using MountPtr = std::shared_ptr<Mount>;
using PrototypeName = std::string;
using StructurePtr = std::shared_ptr<Structure>;
using TileCoord = Sdk::Vector2I;
