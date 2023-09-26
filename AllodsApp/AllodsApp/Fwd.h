#pragma once

#include <LaggySdk/Vector.h>


class Game;
using PrototypeName = std::string;
class Session;
class Structure;
struct StructurePrototype;
using StructurePtr = std::shared_ptr<Structure>;
class Tile;
using TileCoord = Sdk::Vector2I;
class Location;
struct BuildDraftInfo;
class IBehaviorModel;
using BehaviorModelPtr = std::shared_ptr<IBehaviorModel>;
struct Scenario;
class IOverlay;
