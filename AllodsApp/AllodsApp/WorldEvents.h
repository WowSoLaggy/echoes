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
