#include "stdafx.h"
#include "ObjectsSpawner.h"

#include "PrototypesCollection.h"
#include "Location.h"
#include "Structure.h"


StructurePtr ObjectsSpawner::spawnStructure(const PrototypeName& i_name, Location& i_location, const TileCoord& i_coord)
{
  const auto& prototype = PrototypesCollection::getStructurePrototype(i_name);
  return spawnStructure(prototype, i_location, i_coord);
}

StructurePtr ObjectsSpawner::spawnStructure(const StructurePrototype& i_prototype, Location& i_location, const TileCoord& i_coord)
{
  StructurePtr structure = std::make_shared<Structure>(i_prototype);

  auto& tile = i_location.getOrCreateTile(i_coord);
  tile.setStructure(i_prototype.layer, structure);

  return structure;
}


void ObjectsSpawner::despawnStructure(Location& i_location, const TileCoord& i_tileCoord, const Layer i_layer)
{
  if (auto* tile = i_location.getTile(i_tileCoord))
    tile->resetStructure(i_layer);
}
