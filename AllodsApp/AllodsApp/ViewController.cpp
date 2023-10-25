#include "stdafx.h"
#include "ViewController.h"

#include "Avatar.h"
#include "AvatarView.h"
#include "Game.h"
#include "Location.h"
#include "LocationEvents.h"
#include "Object.h"
#include "ObjectView.h"
#include "Prototypes.h"
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

  Objects objectsToDraw;
  Avatars avatarsToDraw;

  for (const auto& [coord, tilePtr] : d_location->getTiles())
  {
    const auto& tile = SAFE_DEREF(tilePtr);
    d_tileView.render(shader, coord, tile);

    const auto& tileObjects = tile.getObjects();
    objectsToDraw.insert(objectsToDraw.end(), tileObjects.begin(), tileObjects.end());

    const auto& tileAvatars = tile.getAvatars();
    avatarsToDraw.insert(avatarsToDraw.end(), tileAvatars.begin(), tileAvatars.end());
  }

  renderObjects(objectsToDraw);
  renderAvatars(avatarsToDraw);

  if (d_overlay)
    d_overlayView.render(shader, d_location->getTiles(), *d_overlay);
  d_buildModeView.render(shader);
}

void ViewController::renderObjects(const Objects& i_objects)
{
  const ObjectView objectView(SAFE_DEREF(d_locationShader));

  for (const auto objectPtr : i_objects)
  {
    const auto& object = SAFE_DEREF(objectPtr);
    objectView.render(object.getPrototype().texture, object.getPosition(), object.getAnimationPlayer().getCurrentFrame());
  }
}

void ViewController::renderAvatars(const Avatars& i_avatars)
{
  const AvatarView avatarView(SAFE_DEREF(d_locationShader));

  for (const auto avatarPtr : i_avatars)
  {
    const auto& avatar = SAFE_DEREF(avatarPtr);
    avatarView.render(avatar.getPrototype().texture, avatar.getPosition(), avatar.getAnimationPlayer().getCurrentFrame());
  }
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
