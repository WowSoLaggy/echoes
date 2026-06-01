#pragma once

#include "FixtureLocations.h"
#include "Fwd.h"
#include "Layers.h"

#include <LaggySdk/Vector.h>


class ObjectsSpawner
{
public:

  static StructurePtr spawnStructure(
    const PrototypeName& i_name, Location& i_location, const TileCoord& i_coord);
  static StructurePtr spawnStructure(
    PrototypePtr i_prototype, Location& i_location, const TileCoord& i_coord);
  static void despawnStructure(
    Location& i_location, const TileCoord& i_tileCoord, Layer i_layer);
  
  static MountPtr spawnMount(
    const PrototypeName& i_name, Structure& i_structure, FixtureLocation i_location);
  static MountPtr spawnMount(
    PrototypePtr i_prototype, Structure& i_structure, FixtureLocation i_location);
  static void despawnMount(Structure& i_structure, FixtureLocation i_location);
  static void despawnMount(Location& i_location, const TileCoord& i_coord, const Mount& i_mount);

  static ObjectPtr spawnObject(
    const PrototypeName& i_name, Location& i_location, Sdk::Vector2F i_position);
  static ObjectPtr spawnObject(
    PrototypePtr i_prototype, Location& i_location, Sdk::Vector2F i_position);
  static void despawnObject(Location& i_location, Object& i_object);

  static AvatarPtr spawnAvatar(
    const PrototypeName& i_name, Location& i_location, Sdk::Vector2F i_position);
  static AvatarPtr spawnAvatar(
    PrototypePtr i_prototype, Location& i_location, Sdk::Vector2F i_position);
  static void despawnAvatar(Location& i_location, Avatar& i_avatar);

private:
  ObjectsSpawner() = delete;
};
