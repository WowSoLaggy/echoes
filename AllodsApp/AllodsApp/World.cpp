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
