#include "stdafx.h"
#include "MountBuilder.h"

#include "Constants.h"
#include "Location.h"
#include "Mount.h"
#include "ObjectsSpawner.h"
#include "Prototypes.h"
#include "Structure.h"


MountBuilder::MountBuilder(
  Location& i_location, const TileCoord& i_tileCoords,
  PrototypePtr i_prototype, const FixtureLocation i_fixtureLocation)
  : d_location(i_location)
  , d_tileCoords(i_tileCoords)
  , d_prototype(i_prototype)
  , d_fixtureLocation(i_fixtureLocation)
{
}


bool MountBuilder::canBeBuilt() const
{
  const auto structure = getStructureWithFixture();
  if (!structure)
    return false;

  const auto fixture = structure->getFixture();
  CONTRACT_ASSERT(fixture);

  const auto mountPtr = fixture->getMount(d_fixtureLocation);
  if (!mountPtr)
    return true;

  return mountPtr->getMountPrototype() != SAFE_DEREF(d_prototype);
}

void MountBuilder::build() const
{
  const auto structure = getStructureWithFixture();
  CONTRACT_EXPECT(structure);

  ObjectsSpawner::despawnMount(*structure, d_fixtureLocation);
  const auto mountPtr = ObjectsSpawner::spawnMount(d_prototype, *structure, d_fixtureLocation);
  SAFE_DEREF(mountPtr).setTemperature(Constants::DefaultEntityTemperature);
}


StructurePtr MountBuilder::getStructureWithFixture() const
{
  const auto tile = d_location.getTile(d_tileCoords);
  if (!tile)
    return nullptr;

  const auto& layers = tile->getLayers();
  for (auto it = layers.rbegin(); it != layers.rend(); ++it)
  {
    const auto structure = it->second;
    CONTRACT_EXPECT(structure);

    if (structure->getStructurePrototype().fixture)
      return structure;
  }

  return nullptr;
}
