#include "stdafx.h"
#include "ObjectBuilder.h"

#include "Constants.h"
#include "Location.h"
#include "Object.h"
#include "ObjectsSpawner.h"
#include "TileUtils.h"


ObjectBuilder::ObjectBuilder(Location& i_location, const Sdk::Vector2F& i_position, PrototypePtr i_prototype)
  : d_location(i_location)
  , d_position(i_position)
  , d_prototype(i_prototype)
{
}


bool ObjectBuilder::canBeBuilt() const
{
  return !hasStructureAtWallLayer();
}

void ObjectBuilder::build() const
{
  const auto objectPtr = ObjectsSpawner::spawnObject(d_prototype, d_location, d_position);
  SAFE_DEREF(objectPtr).setTemperature(Constants::DefaultEntityTemperature);
}


bool ObjectBuilder::hasStructureAtWallLayer() const
{
  const auto tileCoords = TileUtils::getTileCoords(d_position);
  const auto tile = d_location.getTile(tileCoords);
  if (!tile)
    return false;

  return tile->getStructure(Layer::Wall) != nullptr;
}
