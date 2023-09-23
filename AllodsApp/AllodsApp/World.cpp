#include "stdafx.h"
#include "World.h"


void World::update(const double i_dt)
{
  for (auto& [_, tile] : d_tiles)
    tile.update(i_dt);
}


const Tiles& World::getTiles() const
{
  return d_tiles;
}

Tile& World::getOrCreateTile(const TileCoord& i_coord)
{
  return d_tiles[i_coord];
}

Tile* World::getTile(const TileCoord& i_coord)
{
  const auto it = d_tiles.find(i_coord);
  return it == d_tiles.end() ? nullptr : &it->second;
}

const Tile* World::getTile(const TileCoord& i_coord) const
{
  const auto it = d_tiles.find(i_coord);
  return it == d_tiles.end() ? nullptr : &it->second;
}
