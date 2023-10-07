#include "stdafx.h"
#include "ObjectsSpawner.h"

#include "PrototypesCollection.h"
#include "Location.h"
#include "Mount.h"
#include "Object.h"
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

void ObjectsSpawner::despawnMount(Structure& i_structure, FixtureLocation i_location)
{
  auto fixture = i_structure.getFixture();
  CONTRACT_EXPECT(fixture);

  fixture->resetMount(i_location);
}


ObjectPtr ObjectsSpawner::spawnObject(
  const PrototypeName& i_name, Location& i_location, Sdk::Vector2I i_position)
{
  const auto& prototype = PrototypesCollection::getObjectPrototype(i_name);
  return spawnObject(prototype, i_location, i_position);
}

ObjectPtr ObjectsSpawner::spawnObject(
  const ObjectPrototype& i_prototype, Location& i_location, Sdk::Vector2I i_position)
{
  ObjectPtr object = std::make_shared<Object>(i_prototype);
  object->setPosition(std::move(i_position));

  return object;
}

void ObjectsSpawner::despawnObject(Location& i_location, Object& i_object)
{
  auto& objects = i_location.getObjects();
  objects.erase(std::remove_if(objects.begin(), objects.end(), [&](const auto i_objectPtr) {
    return &i_object == i_objectPtr.get();
    }), objects.end());
}
