#include "stdafx.h"
#include "World.h"

#include "WorldEvents.h"


void World::setTerrain(std::unique_ptr<Terrain> i_terrain)
{
  CONTRACT_EXPECT(d_terrain.get() != i_terrain.get());

  if (d_terrain)
    notify(TerrainRemovedEvent(*d_terrain));

  d_terrain = std::move(i_terrain);

  if (d_terrain)
    notify(TerrainAddedEvent(*d_terrain));
}

Terrain* World::getTerrain() const
{
  return d_terrain.get();
}
