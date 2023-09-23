#include "stdafx.h"
#include "Session.h"

#include "SessionEvents.h"
#include "WorldEvents.h"

#include <LaggyDx/FreeCamera2Controller.h>


Session::Session()
  : d_buildManager(*this)
{
  d_camera = Dx::ICamera2::create();
  d_inputController = std::make_unique<Dx::FreeCamera2Controller>(*d_camera);
}


void Session::update()
{
}

void Session::onMouseMove()
{
  d_buildManager.onMouseMove();
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


BuildManager& Session::getBuildManger()
{
  return d_buildManager;
}


Dx::ICamera2& Session::getCamera() const
{
  return SAFE_DEREF(d_camera);
}


void Session::enableGodMode(const bool i_silent)
{
  if (d_godMode)
    return;

  d_godMode = true;
  if (!i_silent)
    notify(GodModeEvent(d_godMode));
}

void Session::disableGodMode(const bool i_silent)
{
  if (!d_godMode)
    return;

  d_godMode = false;
  if (!i_silent)
    notify(GodModeEvent(d_godMode));
}

bool Session::isGodMode() const
{
  return d_godMode;
}
