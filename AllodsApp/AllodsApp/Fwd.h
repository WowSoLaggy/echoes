#pragma once

#include <LaggySdk/Vector.h>


class Avatar;
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
class World;

struct AvatarPrototype;
struct BuildDraftInfo;
struct BuildMountDraftInfo;
struct BuildObjectDraftInfo;
struct GameSettings;
struct MountPrototype;
struct ObjectPrototype;
struct Prototype;
struct Scenario;
struct StructurePrototype;

using AvatarPtr = std::shared_ptr<Avatar>;
using Avatars = std::vector<AvatarPtr>;
using BehaviorModelPtr = std::shared_ptr<IBehaviorModel>;
using EntityPtr = std::shared_ptr<Entity>;
using FixturePtr = std::shared_ptr<Fixture>;
using Locations = std::vector<std::shared_ptr<Location>>;
using MountPtr = std::shared_ptr<Mount>;
using ObjectPtr = std::shared_ptr<Object>;
using Objects = std::vector<ObjectPtr>;
using PrototypeName = std::string;
using PrototypePtr = std::shared_ptr<Prototype>;
using StructurePtr = std::shared_ptr<Structure>;
using TileCoord = Sdk::Vector2I;
using Tiles = std::unordered_map<TileCoord, std::shared_ptr<Tile>, Sdk::Vector2_hash>;
