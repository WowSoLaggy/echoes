#include "stdafx.h"
#include "ObjectsSpawner.h"

#include "PrototypesCollection.h"
#include "Structure.h"
#include "World.h"


StructurePtr ObjectsSpawner::spawnStructure(const PrototypeName& i_name, World& i_world, const TileCoord& i_coord)
{
  const auto& prototype = PrototypesCollection::getStructurePrototype(i_name);
  return spawnStructure(prototype, i_world, i_coord);
}

StructurePtr ObjectsSpawner::spawnStructure(const StructurePrototype& i_prototype, World& i_world, const TileCoord& i_coord)
{
  StructurePtr structure = std::make_shared<Structure>(i_prototype);

  auto& tile = i_world.getOrCreateTile(i_coord);
  tile.setStructure(i_prototype.layer, structure);

  return structure;
}


void ObjectsSpawner::despawnStructure(World& i_world, const TileCoord& i_tileCoord, const Layer i_layer)
{
  if (auto* tile = i_world.getTile(i_tileCoord))
    tile->resetStructure(i_layer);
}
