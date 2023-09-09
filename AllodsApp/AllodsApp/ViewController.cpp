#include "stdafx.h"
#include "ViewController.h"

#include "Game.h"
#include "Session.h"
#include "SessionEvents.h"
#include "World.h"
#include "WorldEvents.h"

#include <LaggyDx/Renderer2dGuard.h>


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
  if (d_terrainView)
    d_terrainView->update(i_dt);
}

void ViewController::render()
{
  if (d_terrainView)
    d_terrainView->render();
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

  else if (const auto* event = dynamic_cast<const TerrainAddedEvent*>(&i_event))
    onTerrainAdded(event->getTerrain());
  else if (const auto* event = dynamic_cast<const TerrainRemovedEvent*>(&i_event))
    onTerrainRemoved();
}


void ViewController::onSessionAttached(Session& i_session)
{
  connectTo(i_session);
  
  if (auto* world = i_session.getWorld())
    onWorldAdded(*world);
}

void ViewController::onSessionDetached(Session& i_session)
{
  if (auto* world = i_session.getWorld())
    onWorldRemoved(*world);
  
  disconnectFrom(i_session);
}

void ViewController::onWorldAdded(World& i_world)
{
  connectTo(i_world);

  if (const auto* terrain = i_world.getTerrain())
    onTerrainAdded(*terrain);
}

void ViewController::onWorldRemoved(World& i_world)
{
  onTerrainRemoved();

  disconnectFrom(i_world);
}

void ViewController::onTerrainAdded(const Terrain& i_terrain)
{
  CONTRACT_EXPECT(d_terrainView == nullptr);

  d_terrainView = std::make_unique<TerrainView>(i_terrain);
}

void ViewController::onTerrainRemoved()
{
  d_terrainView.reset();
}
