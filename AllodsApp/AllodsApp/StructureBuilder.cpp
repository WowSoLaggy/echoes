#include "stdafx.h"
#include "StructureBuilder.h"

#include "Location.h"
#include "ObjectsSpawner.h"
#include "Prototypes.h"
#include "PrototypeUtils.h"
#include "Structure.h"


StructureBuilder::StructureBuilder(Location& i_location, const TileCoord& i_tileCoords, PrototypePtr i_prototype)
  : d_location(i_location)
  , d_tileCoords(i_tileCoords)
  , d_prototype(i_prototype)
{
}


bool StructureBuilder::canBeBuilt() const
{
  if (doesTileAlreadyHaveTheSameStructure())
    return false;

  const auto& structurePrototype = PrototypeUtils::convert<StructurePrototype>(d_prototype);
  if (structurePrototype.layer == Layer::Lowest)
    return true;

  if (doesWallBlocksFurniture())
    return false;

  if (!doesTileHaveLowerLayerWithSupport())
    return false;

  return true;
}

void StructureBuilder::build() const
{
  const auto& structurePrototype = PrototypeUtils::convert<StructurePrototype>(d_prototype);
  ObjectsSpawner::despawnStructure(d_location, d_tileCoords, structurePrototype.layer);
  ObjectsSpawner::spawnStructure(d_prototype, d_location, d_tileCoords);
}


bool StructureBuilder::doesTileHaveLowerLayerWithSupport() const
{
  const auto tile = d_location.getTile(d_tileCoords);
  if (!tile)
    return false;

  const auto& structurePrototype = PrototypeUtils::convert<StructurePrototype>(d_prototype);
  const auto layerRef = structurePrototype.layer;

  for (const auto& [layer, structurePtr] : tile->getLayers())
  {
    CONTRACT_EXPECT(structurePtr);

    if (layer >= layerRef)
      return false;

    if (structurePtr->getStructurePrototype().support)
      return true;
  }

  return false;
}

bool StructureBuilder::doesTileAlreadyHaveTheSameStructure() const
{
  const auto tile = d_location.getTile(d_tileCoords);
  if (!tile)
    return false;

  const auto& structurePrototype = PrototypeUtils::convert<StructurePrototype>(d_prototype);

  if (const auto structurePtr = tile->getStructure(structurePrototype.layer))
    return structurePtr->getStructurePrototype() == structurePrototype;

  return false;
}

bool StructureBuilder::doesWallBlocksFurniture() const
{
  const auto& structurePrototype = PrototypeUtils::convert<StructurePrototype>(d_prototype);
  if (structurePrototype.layer != Layer::Furniture)
    return false;

  const auto tile = d_location.getTile(d_tileCoords);
  if (!tile)
    return false;

  const auto structurePtr = tile->getStructure(Layer::Wall);
  return structurePtr != nullptr;
}
