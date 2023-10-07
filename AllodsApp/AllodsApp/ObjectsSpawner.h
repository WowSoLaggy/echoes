#pragma once

#include "FixtureLocations.h"
#include "Fwd.h"
#include "Layers.h"


class ObjectsSpawner
{
public:

  static StructurePtr spawnStructure(
    const PrototypeName& i_name, Location& i_location, const TileCoord& i_coord);
  static StructurePtr spawnStructure(
    const StructurePrototype& i_prototype, Location& i_location, const TileCoord& i_coord);
  static void despawnStructure(
    Location& i_location, const TileCoord& i_tileCoord, Layer i_layer);
  
  static MountPtr spawnMount(
    const PrototypeName& i_name, StructurePtr i_structure, FixtureLocation i_location);
  static MountPtr spawnMount(
    const MountPrototype& i_prototype, StructurePtr i_structure, FixtureLocation i_location);
  static void despawnMount(
    StructurePtr i_structure, FixtureLocation i_location);

private:
  ObjectsSpawner() = delete;
};
