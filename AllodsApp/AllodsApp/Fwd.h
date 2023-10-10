#pragma once

#include <LaggySdk/Vector.h>


class Entity;
class Fixture;
class Game;
class IBehaviorModel;
class IOverlay;
class Location;
class Mount;
class Object;
class Session;
class Structure;
class Tile;

struct BuildDraftInfo;
struct BuildMountDraftInfo;
struct MountPrototype;
struct ObjectPrototype;
struct Prototype;
struct Scenario;
struct StructurePrototype;

using BehaviorModelPtr = std::shared_ptr<IBehaviorModel>;
using FixturePtr = std::shared_ptr<Fixture>;
using MountPtr = std::shared_ptr<Mount>;
using ObjectPtr = std::shared_ptr<Object>;
using Objects = std::vector<ObjectPtr>;
using PrototypeName = std::string;
using StructurePtr = std::shared_ptr<Structure>;
using TileCoord = Sdk::Vector2I;
