#include "stdafx.h"
#include "ViewController.h"

#include "Game.h"
#include "Location.h"
#include "LocationEvents.h"
#include "Session.h"
#include "SessionEvents.h"


ViewController::ViewController(Game& i_game)
{
  connectTo(i_game);
  if (auto* session = i_game.getSession())
    onSessionAttached(*session);
}

ViewController::~ViewController()
{
  disconnectFromAll();
}


void ViewController::update(double i_dt)
{
}

void ViewController::render()
{
  if (!d_location)
    return;

  const auto& shader = SAFE_DEREF(d_locationShader);

  d_backgroundView.render(shader, SAFE_DEREF(d_camera));
  d_tileView.render(shader, d_location->getTiles());
  d_objectView.render(shader, d_location->getObjects());

  if (d_overlay)
    d_overlayView.render(shader, d_location->getTiles(), *d_overlay);
  d_buildModeView.render(shader);
}


void ViewController::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const SessionAttachedEvent*>(&i_event))
    onSessionAttached(event->getSession());
  else if (const auto* event = dynamic_cast<const SessionDetachedEvent*>(&i_event))
    onSessionDetached(event->getSession());

  else if (const auto* event = dynamic_cast<const LocationAddedEvent*>(&i_event))
    onLocationAdded(event->getLocation());
  else if (const auto* event = dynamic_cast<const LocationRemovedEvent*>(&i_event))
    onLocationRemoved(event->getLocation());

  else if (const auto* event = dynamic_cast<const BuildDraftSetEvent*>(&i_event))
    onBuildDraftSet(event->getInfo());

  else if (const auto* event = dynamic_cast<const OverlaySetEvent*>(&i_event))
    onOverlaySet(event->getOverlay());
}


void ViewController::onSessionAttached(Session& i_session)
{
  connectTo(i_session);
  connectTo(i_session.getBuildManger());

  d_camera = &i_session.getCamera();
  
  d_locationShader = Dx::ISpriteShader::create(d_camera);
  CONTRACT_ASSERT(d_locationShader);

  if (auto* location = i_session.getCurrentLocation())
    onLocationAdded(*location);
}

void ViewController::onSessionDetached(Session& i_session)
{
  if (auto* location = i_session.getCurrentLocation())
    onLocationRemoved(*location);

  d_camera = nullptr;

  d_locationShader.reset();
  
  disconnectFrom(i_session.getBuildManger());
  disconnectFrom(i_session);
}

void ViewController::onLocationAdded(Location& i_location)
{
  d_location = &i_location;
  connectTo(i_location);
}

void ViewController::onLocationRemoved(Location& i_location)
{
  d_overlay = nullptr;

  disconnectFrom(i_location);
  d_location = nullptr;
}

void ViewController::onBuildDraftSet(std::shared_ptr<BuildDraftInfo> i_buildDraftInfo)
{
  d_buildModeView.setBuildDraft(i_buildDraftInfo);
}

void ViewController::onOverlaySet(const IOverlay* i_overlay)
{
  d_overlay = i_overlay;
}
