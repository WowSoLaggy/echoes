#include "stdafx.h"
#include "ObjectsSpawner.h"

#include "PrototypesCollection.h"
#include "Location.h"
#include "Mount.h"
#include "Structure.h"


StructurePtr ObjectsSpawner::spawnStructure(
  const PrototypeName& i_name, Location& i_location, const TileCoord& i_coord)
{
  const auto& prototype = PrototypesCollection::getStructurePrototype(i_name);
  return spawnStructure(prototype, i_location, i_coord);
}

StructurePtr ObjectsSpawner::spawnStructure(
  const StructurePrototype& i_prototype, Location& i_location, const TileCoord& i_coord)
{
  StructurePtr structure = std::make_shared<Structure>(i_prototype);

  auto& tile = i_location.getOrCreateTile(i_coord);
  tile.setStructure(i_prototype.layer, structure);

  return structure;
}

void ObjectsSpawner::despawnStructure(
  Location& i_location, const TileCoord& i_tileCoord, const Layer i_layer)
{
  if (auto* tile = i_location.getTile(i_tileCoord))
    tile->resetStructure(i_layer);
}


MountPtr ObjectsSpawner::spawnMount(
  const PrototypeName& i_name, Structure& i_structure, FixtureLocation i_location)
{
  const auto& prototype = PrototypesCollection::getMountPrototype(i_name);
  return spawnMount(prototype, i_structure, i_location);
}

MountPtr ObjectsSpawner::spawnMount(
  const MountPrototype& i_prototype, Structure& i_structure, FixtureLocation i_location)
{
  auto fixture = i_structure.getFixture();
  CONTRACT_EXPECT(fixture);

  MountPtr mount = std::make_shared<Mount>(i_prototype);
  fixture->setMount(i_location, mount);

  return mount;
}

void ObjectsSpawner::despawnMount(
  Structure& i_structure, FixtureLocation i_location)
{
  auto fixture = i_structure.getFixture();
  CONTRACT_EXPECT(fixture);

  fixture->resetMount(i_location);
}
