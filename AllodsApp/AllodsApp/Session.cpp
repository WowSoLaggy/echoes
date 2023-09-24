#include "stdafx.h"
#include "Session.h"

#include "SessionEvents.h"
#include "WorldEvents.h"

#include <LaggyDx/FreeCamera2Controller.h>


Session::Session()
  : d_buildManager(*this)
  , d_interactionManager(*this)
{
  d_camera = Dx::ICamera2::create();
  attachFreeCameraController();
}


void Session::update(const double i_dt)
{
  if (d_world)
    d_world->update(i_dt);
}

void Session::onMouseMove()
{
  d_buildManager.onMouseMove();
}

bool Session::onMouseClick(Dx::MouseKey i_key)
{
  if (d_buildManager.onMouseClick(i_key))
    return true;

  if (d_interactionManager.onMouseClick(i_key))
    return true;

  return false;
}

void Session::onMouseRelease(Dx::MouseKey i_key)
{
  d_buildManager.onMouseRelease(i_key);
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


void Session::attachFreeCameraController()
{
  d_inputController = std::make_unique<Dx::FreeCamera2Controller>(*d_camera);
}

void Session::detachFreeCameraController()
{
  d_inputController.reset();
}


void Session::onEscape()
{
  if (d_buildManager.isInBuildMode() || d_buildManager.isInRemovalMode())
  {
    notify(ExitBuildRemovalEvent());
    return;
  }

  d_pause ? unpause() : pause();
}

void Session::pause(const bool i_silent)
{
  detachFreeCameraController();
  d_pause = true;

  if (!i_silent)
    notify(PauseEvent());
}

void Session::unpause(const bool i_silent)
{
  d_pause = false;
  attachFreeCameraController();

  if (!i_silent)
    notify(UnpauseEvent());
}
