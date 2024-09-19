#include "stdafx.h"
#include "ObjectsSpawner.h"

#include "Avatar.h"
#include "Location.h"
#include "Mount.h"
#include "Object.h"
#include "PrototypesCollection.h"
#include "Structure.h"
#include "TileUtils.h"


StructurePtr ObjectsSpawner::spawnStructure(
  const PrototypeName& i_name, Location& i_location, const TileCoord& i_coord)
{
  const auto& prototype = PrototypesCollection::getStructurePrototype(i_name);
  return spawnStructure(prototype, i_location, i_coord);
}

StructurePtr ObjectsSpawner::spawnStructure(
  PrototypePtr i_prototype, Location& i_location, const TileCoord& i_coord)
{
  const auto& structurePrototype = SAFE_DEREF(dynamic_cast<const StructurePrototype*>(i_prototype.get()));

  StructurePtr structure = std::make_shared<Structure>(i_prototype);

  auto& tile = i_location.getOrCreateTile(i_coord);
  tile.setStructure(structurePrototype.layer, structure);

  return structure;
}

void ObjectsSpawner::despawnStructure(
  Location& i_location, const TileCoord& i_tileCoord, const Layer i_layer)
{
  if (auto tile = i_location.getTile(i_tileCoord))
    tile->resetStructureIfExists(i_layer);
}


MountPtr ObjectsSpawner::spawnMount(
  const PrototypeName& i_name, Structure& i_structure, FixtureLocation i_location)
{
  const auto& prototype = PrototypesCollection::getMountPrototype(i_name);
  return spawnMount(prototype, i_structure, i_location);
}

MountPtr ObjectsSpawner::spawnMount(
  PrototypePtr i_prototype, Structure& i_structure, FixtureLocation i_location)
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

void ObjectsSpawner::despawnMount(Location& i_location, const TileCoord& i_coord, const Mount& i_mount)
{
  const auto& tile = SAFE_DEREF(i_location.getTile(i_coord));
  for (const auto& [_, structurePtr] : tile.getLayers())
  {
    const auto& structure = SAFE_DEREF(structurePtr);
    if (const auto fixture = structure.getFixture())
    {
      for (const auto& [layer, mountPtr] : fixture->getMounts())
      {
        if (mountPtr && mountPtr.get() == &i_mount)
        {
          fixture->resetMount(layer);
          return;
        }
      }
    }
  }

  CONTRACT_THROW();
}


ObjectPtr ObjectsSpawner::spawnObject(
  const PrototypeName& i_name, Location& i_location, Sdk::Vector2I i_position)
{
  const auto& prototype = PrototypesCollection::getObjectPrototype(i_name);
  return spawnObject(prototype, i_location, i_position);
}

ObjectPtr ObjectsSpawner::spawnObject(
  PrototypePtr i_prototype, Location& i_location, Sdk::Vector2I i_position)
{
  const auto tileCoord = TileUtils::getTileCoords(i_position);
  auto& tile = i_location.getOrCreateTile(tileCoord);

  ObjectPtr object = std::make_shared<Object>(i_prototype);
  object->setPosition(std::move(i_position));

  tile.addObject(object);

  return object;
}

void ObjectsSpawner::despawnObject(Location& i_location, Object& i_object)
{
  const auto tileCoord = TileUtils::getTileCoords(i_object.getPosition());
  auto& tile = i_location.getOrCreateTile(tileCoord);

  tile.removeObject(i_object);
}


AvatarPtr ObjectsSpawner::spawnAvatar(
  const PrototypeName& i_name, Location& i_location, Sdk::Vector2I i_position)
{
  const auto& prototype = PrototypesCollection::getAvatarPrototype(i_name);
  return spawnAvatar(prototype, i_location, i_position);
}

AvatarPtr ObjectsSpawner::spawnAvatar(
  PrototypePtr i_prototype, Location& i_location, Sdk::Vector2I i_position)
{
  const auto tileCoord = TileUtils::getTileCoords(i_position);
  auto& tile = i_location.getOrCreateTile(tileCoord);

  AvatarPtr avatar = std::make_shared<Avatar>(i_prototype);
  avatar->setPosition(std::move(i_position));

  tile.addAvatar(avatar);

  return avatar;
}

void ObjectsSpawner::despawnAvatar(Location& i_location, Avatar& i_avatar)
{
  const auto tileCoord = TileUtils::getTileCoords(i_avatar.getPosition());
  auto& tile = i_location.getOrCreateTile(tileCoord);

  tile.removeAvatar(i_avatar);
}
