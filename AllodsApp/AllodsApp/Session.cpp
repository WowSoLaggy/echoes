#include "stdafx.h"
#include "Session.h"

#include "WorldEvents.h"


void Session::setWorld(std::unique_ptr<World> i_world)
{
  CONTRACT_EXPECT(d_world.get() != i_world.get());

  if (d_world)
    notify(WorldRemovedEvent(*d_world));

  d_world = std::move(i_world);

  if (d_world)
    notify(WorldAddedEvent(*d_world));
}

World* Session::getWorld() const
{
  return d_world.get();
}
