#include "stdafx.h"
#include "Location.h"

#include "Avatar.h"
#include "Object.h"

#include <LaggyDx/Simulation.h>


namespace
{
  std::string createTileTag(const TileCoord& i_coord)
  {
    return "tile." + std::to_string(i_coord.x) + "." + std::to_string(i_coord.y);
  }

} // anonym NS


Location::Location()
  : d_tileCollection(*this)
{
}


void Location::pushFields()
{
  pushField("name", d_name);

  for (auto& [coord, tile] : d_tiles)
    pushObject(createTileTag(coord), tile);

  for (auto& objectPtr : d_objects)
    pushObject("object", SAFE_DEREF(objectPtr));

  for (auto& avatarPtr : d_avatars)
    pushObject("avatar", SAFE_DEREF(avatarPtr));
}


void Location::setName(std::string i_name)
{
  d_name = std::move(i_name);
}

const std::string& Location::getName() const
{
  return d_name;
}


void Location::update(const double i_dt)
{
  Dx::thd::Simulation().update(i_dt, d_tileCollection);

  for (auto& [_, tile] : d_tiles)
    tile.update(i_dt);

  for (auto objPtr : d_objects)
    SAFE_DEREF(objPtr).update(i_dt);
  for (auto avatarPtr : d_avatars)
    SAFE_DEREF(avatarPtr).update(i_dt);
}


int Location::getMinX() const
{
  return d_minX;
}

int Location::getMinY() const
{
  return d_minY;
}

int Location::getMaxX() const
{
  return d_maxX;
}

int Location::getMaxY() const
{
  return d_maxY;
}


const Tiles& Location::getTiles() const
{
  return d_tiles;
}

Tile& Location::getOrCreateTile(const TileCoord& i_coord)
{
  if (auto* tile = getTile(i_coord))
    return *tile;

  d_minX = std::min(d_minX, i_coord.x);
  d_minY = std::min(d_minY, i_coord.y);
  d_maxX = std::max(d_maxX, i_coord.x);
  d_maxY = std::max(d_maxY, i_coord.y);

  return d_tiles[i_coord];
}

Tile* Location::getTile(const TileCoord& i_coord)
{
  const auto it = d_tiles.find(i_coord);
  return it == d_tiles.end() ? nullptr : &it->second;
}

const Tile* Location::getTile(const TileCoord& i_coord) const
{
  const auto it = d_tiles.find(i_coord);
  return it == d_tiles.end() ? nullptr : &it->second;
}


Objects& Location::getObjects()
{
  return d_objects;
}

const Objects& Location::getObjects() const
{
  return d_objects;
}


Avatars& Location::getAvatars()
{
  return d_avatars;
}

const Avatars& Location::getAvatars() const
{
  return d_avatars;
}
