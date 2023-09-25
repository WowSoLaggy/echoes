#pragma once

#include "Fwd.h"
#include "Layers.h"


class ObjectsSpawner
{
public:
  ObjectsSpawner() = delete;

  static StructurePtr spawnStructure(const PrototypeName& i_name, Location& i_location, const TileCoord& i_coord);
  static StructurePtr spawnStructure(const StructurePrototype& i_prototype, Location& i_location, const TileCoord& i_coord);
  
  static void despawnStructure(Location& i_location, const TileCoord& i_tileCoord, Layer i_layer);
};
