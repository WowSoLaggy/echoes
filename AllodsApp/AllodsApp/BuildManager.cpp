#include "stdafx.h"
#include "BuildManager.h"

#include "BuildDraftInfo.h"
#include "ObjectsSpawner.h"
#include "Session.h"
#include "SessionEvents.h"
#include "Structure.h"
#include "StructurePrototype.h"
#include "TileUtils.h"

#include <LaggyDx/App.h>


BuildManager::BuildManager(Session& i_session)
  : d_session(i_session)
{
}


void BuildManager::setBuildDraft(const StructurePrototype& i_prototype)
{
  d_buildPrototype = &i_prototype;
  d_buildDraftInfo = std::make_shared<BuildDraftInfo>(BuildDraftInfo(d_buildPrototype->textureName));

  updateBuildDraft();

  notify(BuildDraftSetEvent(d_buildDraftInfo));
}

void BuildManager::resetBuildDraft()
{
  notify(BuildDraftSetEvent(nullptr));
  d_buildPrototype = nullptr;
  d_buildDraftInfo.reset();
}


void BuildManager::onMouseMove()
{
  if (!d_buildDraftInfo)
    return;

  updateBuildDraft();
}

void BuildManager::onMouseClick(Dx::MouseKey i_key)
{
  if (!d_buildDraftInfo)
    return;

  tryBuild();
}


void BuildManager::tryBuild()
{
  CONTRACT_EXPECT(d_buildDraftInfo);
  if (!d_buildDraftInfo->allowed)
    return;

  build();
}

void BuildManager::build()
{
  CONTRACT_EXPECT(d_buildPrototype);
  CONTRACT_EXPECT(d_buildDraftInfo);

  auto* world = d_session.getWorld();
  CONTRACT_EXPECT(world);

  ObjectsSpawner::despawnStructure(*world, d_buildDraftInfo->tileCoords, d_buildPrototype->layer);
  ObjectsSpawner::spawnStructure(*d_buildPrototype, *world, d_buildDraftInfo->tileCoords);
}


void BuildManager::updateBuildDraft()
{
  updateBuildPosition();
  updateBuildAllowance();
}

void BuildManager::updateBuildPosition()
{
  const auto& mousePos = Dx::App::get().getInputDevice().getMousePosition();
  SAFE_DEREF(d_buildDraftInfo).tileCoords = getTileCoords(mousePos, d_session.getCamera());
}

void BuildManager::updateBuildAllowance()
{
  SAFE_DEREF(d_buildDraftInfo).allowed = canBeBuilt();
}

bool BuildManager::canBeBuilt() const
{
  CONTRACT_EXPECT(d_buildPrototype);

  if (d_buildPrototype->layer == Layer::Lowest)
    return true;

  return doesTileHaveLowerLayerWithSupport();
}

const Tile* BuildManager::getTileForBuildDraft() const
{
  if (const auto* world = d_session.getWorld())
    return world->getTile(SAFE_DEREF(d_buildDraftInfo).tileCoords);
  return nullptr;
}

bool BuildManager::doesTileHaveLowerLayerWithSupport() const
{
  const auto* tile = getTileForBuildDraft();
  if (!tile)
    return false;

  CONTRACT_EXPECT(d_buildPrototype);

  for (const auto& [layer, structurePtr] : tile->getLayers())
  {
    if (layer >= d_buildPrototype->layer)
      return false;

    if (structurePtr->getPrototype().support)
      return true;
  }

  return false;
}
