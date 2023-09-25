#include "stdafx.h"
#include "Location.h"


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
  for (auto& [_, tile] : d_tiles)
    tile.update(i_dt);
}


const Tiles& Location::getTiles() const
{
  return d_tiles;
}

Tile& Location::getOrCreateTile(const TileCoord& i_coord)
{
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
