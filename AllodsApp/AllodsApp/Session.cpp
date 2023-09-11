#include "stdafx.h"
#include "Session.h"

#include "WorldEvents.h"

#include <LaggyDx/FreeCamera2Controller.h>


Session::Session()
{
  d_camera = Dx::ICamera2::create();
  d_inputController = std::make_unique<Dx::FreeCamera2Controller>(*d_camera);
}


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


Dx::ICamera2& Session::getCamera() const
{
  return SAFE_DEREF(d_camera);
}
