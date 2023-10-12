#include "stdafx.h"
#include "StructureBuilder.h"

#include "Location.h"
#include "ObjectsSpawner.h"
#include "Prototypes.h"
#include "Structure.h"


StructureBuilder::StructureBuilder(Location& i_location, const TileCoord& i_tileCoords, const StructurePrototype& i_prototype)
  : d_location(i_location)
  , d_tileCoords(i_tileCoords)
  , d_prototype(i_prototype)
{
}


bool StructureBuilder::canBeBuilt() const
{
  if (doesTileAlreadyHaveTheSameStructure())
    return false;

  if (d_prototype.layer == Layer::Lowest)
    return true;

  if (doesWallBlocksFurniture())
    return false;

  if (!doesTileHaveLowerLayerWithSupport())
    return false;

  return true;
}

void StructureBuilder::build() const
{
  ObjectsSpawner::despawnStructure(d_location, d_tileCoords, d_prototype.layer);
  ObjectsSpawner::spawnStructure(d_prototype, d_location, d_tileCoords);
}


bool StructureBuilder::doesTileHaveLowerLayerWithSupport() const
{
  const auto* tile = d_location.getTile(d_tileCoords);
  if (!tile)
    return false;

  for (const auto& [layer, structurePtr] : tile->getLayers())
  {
    CONTRACT_EXPECT(structurePtr);

    if (layer >= d_prototype.layer)
      return false;

    if (structurePtr->getStructurePrototype().support)
      return true;
  }

  return false;
}

bool StructureBuilder::doesTileAlreadyHaveTheSameStructure() const
{
  const auto* tile = d_location.getTile(d_tileCoords);
  if (!tile)
    return false;

  if (const auto structurePtr = tile->getStructure(d_prototype.layer))
    return structurePtr->getStructurePrototype() == d_prototype;

  return false;
}

bool StructureBuilder::doesWallBlocksFurniture() const
{
  if (d_prototype.layer != Layer::Furniture)
    return false;

  const auto* tile = d_location.getTile(d_tileCoords);
  if (!tile)
    return false;

  const auto structurePtr = tile->getStructure(Layer::Wall);
  return structurePtr != nullptr;
}
