#pragma once

#include <LaggySdk/Vector.h>


class Avatar;
class BehaviorAction;
class CtxMenu;
class CtxMenuContent;
class Entity;
class Fixture;
class Game;
class IBehaviorModel;
class InteractionManager;
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
using BehaviorActionPtr = std::shared_ptr<BehaviorAction>;
using BehaviorActions = std::vector<BehaviorActionPtr>;
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
using TilePtr = std::shared_ptr<Tile>;
using Tiles = std::unordered_map<TileCoord, TilePtr, Sdk::Vector2_hash>;
