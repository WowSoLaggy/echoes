#pragma once

#include "Fwd.h"

#include <LaggySdk/IEvent.h>


class WorldEvent : public Sdk::IEvent
{
public:
  explicit WorldEvent(World& i_world)
    : d_world(i_world)
  {
  }

  World& getWorld() const
  {
    return d_world;
  }

private:
  World& d_world;
};


class WorldAddedEvent : public WorldEvent
{
public:
  using WorldEvent::WorldEvent;
};

class WorldRemovedEvent : public WorldEvent
{
public:
  using WorldEvent::WorldEvent;
};


class TerrainEvent : public Sdk::IEvent
{
public:
  explicit TerrainEvent(const Terrain& i_terrain)
    : d_terrain(i_terrain)
  {
  }

  const Terrain& getTerrain() const
  {
    return d_terrain;
  }

private:
  const Terrain& d_terrain;
};


class TerrainAddedEvent : public TerrainEvent
{
public:
  using TerrainEvent::TerrainEvent;
};

class TerrainRemovedEvent : public TerrainEvent
{
public:
  using TerrainEvent::TerrainEvent;
};
