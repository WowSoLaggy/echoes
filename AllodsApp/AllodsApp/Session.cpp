#include "stdafx.h"
#include "Session.h"

#include "LocationEvents.h"
#include "SessionEvents.h"

#include <LaggyDx/FreeCamera2Controller.h>


Session::Session(Scenario i_scenario)
  : d_scenario(std::move(i_scenario))
  , d_buildManager(*this)
  , d_interactionManager(*this)
{
  d_camera = Dx::ICamera2::create();
  attachFreeCameraController();
}


void Session::pushFields()
{
  pushObject("scenario", d_scenario);
  if (d_world)
    pushObject("world", *d_world);
}


void Session::update(const double i_dt)
{
  if (d_pause)
    return;

  for (auto& location : SAFE_DEREF(d_world).getLocations())
    SAFE_DEREF(location).update(i_dt);
}

void Session::onMouseMove()
{
  if (d_pause)
    return;

  d_buildManager.onMouseMove();
}

bool Session::onMouseClick(Dx::MouseKey i_key)
{
  if (d_pause)
    return false;

  if (d_buildManager.onMouseClick(i_key))
    return true;

  if (d_interactionManager.onMouseClick(i_key))
    return true;

  return false;
}

void Session::onMouseRelease(Dx::MouseKey i_key)
{
  if (d_pause)
    return;

  d_buildManager.onMouseRelease(i_key);
}


const Scenario& Session::getScenario() const
{
  return d_scenario;
}


void Session::setWorld(std::unique_ptr<World> i_world)
{
  d_world = std::move(i_world);
}

World* Session::getWorld() const
{
  return d_world.get();
}


void Session::setCurrentLocation(Location* i_location)
{
  CONTRACT_EXPECT(d_currentLocation != i_location);

  if (d_currentLocation)
    notify(LocationRemovedEvent(*d_currentLocation));

  d_currentLocation = i_location;

  if (d_currentLocation)
    notify(LocationAddedEvent(*d_currentLocation));
}

Location* Session::getCurrentLocation() const
{
  return d_currentLocation;
}


BuildManager& Session::getBuildManger()
{
  return d_buildManager;
}


Dx::ICamera2& Session::getCamera() const
{
  return SAFE_DEREF(d_camera);
}


void Session::enableGodMode()
{
  if (d_godMode)
    return;

  d_godMode = true;

  notify(GodModeEvent(d_godMode));
}

void Session::disableGodMode()
{
  if (!d_godMode)
    return;

  resetOverlay();
  d_godMode = false;

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

bool Session::isPause() const
{
  return d_pause;
}


const IOverlay* Session::getOverlay() const
{
  return d_overlay.get();
}

void Session::setOverlay(const OverlayType i_overlayType)
{
  d_overlay = IOverlay::create(i_overlayType, SAFE_DEREF(getCurrentLocation()));
  notify(OverlaySetEvent(d_overlay.get()));
}

void Session::resetOverlay()
{
  d_overlay.reset();
  notify(OverlaySetEvent(nullptr));
}
