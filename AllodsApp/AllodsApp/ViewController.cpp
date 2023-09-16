#include "stdafx.h"
#include "ViewController.h"

#include "Game.h"
#include "Session.h"
#include "SessionEvents.h"
#include "World.h"
#include "WorldEvents.h"


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
  if (d_world)
  {
    d_backgroundView.render(SAFE_DEREF(d_worldShader), SAFE_DEREF(d_camera));
    d_tileView.render(SAFE_DEREF(d_worldShader), d_world->getTiles());
  }
}


void ViewController::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const SessionAttachedEvent*>(&i_event))
    onSessionAttached(event->getSession());
  else if (const auto* event = dynamic_cast<const SessionDetachedEvent*>(&i_event))
    onSessionDetached(event->getSession());

  else if (const auto* event = dynamic_cast<const WorldAddedEvent*>(&i_event))
    onWorldAdded(event->getWorld());
  else if (const auto* event = dynamic_cast<const WorldRemovedEvent*>(&i_event))
    onWorldRemoved(event->getWorld());
}


void ViewController::onSessionAttached(Session& i_session)
{
  connectTo(i_session);

  d_camera = &i_session.getCamera();
  
  d_worldShader = Dx::ISpriteShader::create(d_camera);
  CONTRACT_ASSERT(d_worldShader);

  if (auto* world = i_session.getWorld())
    onWorldAdded(*world);
}

void ViewController::onSessionDetached(Session& i_session)
{
  if (auto* world = i_session.getWorld())
    onWorldRemoved(*world);

  d_camera = nullptr;

  d_worldShader.reset();
  
  disconnectFrom(i_session);
}

void ViewController::onWorldAdded(World& i_world)
{
  d_world = &i_world;
  connectTo(i_world);
}

void ViewController::onWorldRemoved(World& i_world)
{
  disconnectFrom(i_world);
  d_world = nullptr;
}
