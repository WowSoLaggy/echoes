#pragma once

#include "Fwd.h"
#include "Layers.h"


class ObjectsSpawner
{
public:
  ObjectsSpawner() = delete;

  static StructurePtr spawnStructure(const PrototypeName& i_name, World& i_world, const TileCoord& i_coord);
  static StructurePtr spawnStructure(const StructurePrototype& i_prototype, World& i_world, const TileCoord& i_coord);
  
  static void despawnStructure(World& i_world, const TileCoord& i_tileCoord, Layer i_layer);
};
