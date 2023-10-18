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

  /*for (auto& [coord, tile] : d_tiles)
    pushObject(createTileTag(coord), tile);*/

  /*for (auto& objectPtr : d_objects)
    pushObject("object", SAFE_DEREF(objectPtr));*/

  pushVector("avatars", d_avatars);
}

void Location::onDeserialized()
{
  updateMinMax();
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


const Sdk::RectI& Location::getRect() const
{
  return d_minMaxRect;
}


const Tiles& Location::getTiles() const
{
  return d_tiles;
}

Tile& Location::getOrCreateTile(const TileCoord& i_coord)
{
  if (auto* tile = getTile(i_coord))
    return *tile;

  updateMinMax(i_coord);

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


void Location::updateMinMax(const TileCoord& i_coord)
{
  if (d_tiles.empty())
  {
    d_minMaxRect.p1 = i_coord;
    d_minMaxRect.p2 = i_coord;
  }
  else
  {
    d_minMaxRect.p1.x = std::min(i_coord.x, d_minMaxRect.p1.x);
    d_minMaxRect.p1.y = std::min(i_coord.y, d_minMaxRect.p1.y);
    d_minMaxRect.p2.x = std::max(i_coord.x, d_minMaxRect.p2.x);
    d_minMaxRect.p2.y = std::max(i_coord.y, d_minMaxRect.p2.y);
  }
}

void Location::updateMinMax()
{
  if (d_tiles.empty())
  {
    d_minMaxRect.p1 = Sdk::Vector2I::zero();
    d_minMaxRect.p2 = Sdk::Vector2I::zero();
    return;
  }

  d_minMaxRect.p1 = d_tiles.begin()->first;
  d_minMaxRect.p2 = d_tiles.begin()->first;

  for (const auto& [coord, _] : d_tiles)
    updateMinMax(coord);
}
