#include "stdafx.h"
#include "BuildManager.h"

#include "BuildDraftInfo.h"
#include "ObjectsSpawner.h"
#include "Session.h"
#include "SessionEvents.h"
#include "Structure.h"
#include "StructurePrototype.h"
#include "StructureUtils.h"
#include "TileUtils.h"

#include <LaggyDx/App.h>
#include <LaggyDx/CursorUtils.h>


BuildManager::BuildManager(Session& i_session)
  : d_session(i_session)
{
}


bool BuildManager::isInBuildMode() const
{
  return d_buildPrototype;
}

void BuildManager::setBuildDraft(const StructurePrototype& i_prototype)
{
  stopRemovalMode();

  d_buildPrototype = &i_prototype;
  d_buildDraftInfo = std::make_shared<BuildDraftInfo>();
  d_buildDraftInfo->texture = d_buildPrototype->texture;

  updateBuildDraft();

  notify(BuildDraftSetEvent(d_buildDraftInfo));
}

void BuildManager::resetBuildDraft()
{
  notify(BuildDraftSetEvent(nullptr));
  d_buildPrototype = nullptr;
  d_buildDraftInfo.reset();
}


bool BuildManager::isInRemovalMode() const
{
  return d_isRemovalMode;
}

void BuildManager::startRemovalMode()
{
  resetBuildDraft();
  d_isRemovalMode = true;
}

void BuildManager::stopRemovalMode()
{
  d_isRemovalMode = false;
}


void BuildManager::onMouseMove()
{
  if (d_buildDraftInfo)
  {
    updateBuildDraft();

    if (d_isMutlibuilding)
      tryBuild();
  }
  else if (d_isMutliremoving)
    tryRemove();
}

bool BuildManager::onMouseClick(Dx::MouseKey i_key)
{
  if (i_key == Dx::MouseKey::Right)
  {
    if (d_isMutlibuilding || d_isMutliremoving)
    {
      d_isMutlibuilding = false;
      d_isMutliremoving = false;
      d_lastRemovedCoords.reset();
      return true;
    }
  }

  if (i_key != Dx::MouseKey::Left)
    return false;

  if (d_buildDraftInfo)
  {
    d_isMutlibuilding = true;
    tryBuild();
    return true;
  }
  else if (d_isRemovalMode)
  {
    d_isMutliremoving = true;
    tryRemove();
    return true;
  }

  return false;
}

void BuildManager::onMouseRelease(Dx::MouseKey i_key)
{
  d_isMutlibuilding = false;
  d_isMutliremoving = false;
  d_lastRemovedCoords.reset();
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

  auto* location = d_session.getLocation();
  CONTRACT_EXPECT(location);

  ObjectsSpawner::despawnStructure(*location, d_buildDraftInfo->tileCoords, d_buildPrototype->layer);
  ObjectsSpawner::spawnStructure(*d_buildPrototype, *location, d_buildDraftInfo->tileCoords);

  updateBuildAllowance();
}


void BuildManager::updateBuildDraft()
{
  updateBuildPosition();
  updateBuildAllowance();
}

void BuildManager::updateBuildPosition()
{
  const auto& mousePos = Dx::CursorUtils::getPosition();
  SAFE_DEREF(d_buildDraftInfo).tileCoords = TileUtils::getTileCoords(mousePos, d_session.getCamera());
}

void BuildManager::updateBuildAllowance()
{
  SAFE_DEREF(d_buildDraftInfo).allowed = canBeBuilt();
}

bool BuildManager::canBeBuilt() const
{
  CONTRACT_EXPECT(d_buildPrototype);

  if (doesTileAlreadyHaveTheSameStructure())
    return false;

  if (d_buildPrototype->layer == Layer::Lowest)
    return true;

  if (!doesTileHaveLowerLayerWithSupport())
    return false;

  return true;
}

const Tile* BuildManager::getTileForBuildDraft() const
{
  if (const auto* location = d_session.getLocation())
    return location->getTile(SAFE_DEREF(d_buildDraftInfo).tileCoords);
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

bool BuildManager::doesTileAlreadyHaveTheSameStructure() const
{
  const auto* tile = getTileForBuildDraft();
  if (!tile)
    return false;

  CONTRACT_EXPECT(d_buildPrototype);

  if (const auto structurePtr = tile->getStructure(d_buildPrototype->layer))
    return structurePtr->getPrototype() == *d_buildPrototype;

  return false;
}


void BuildManager::tryRemove()
{
  const auto structure = StructureUtils::getStructureUnderCursor(d_session);
  if (!structure)
    return;

  const auto tileCoords = TileUtils::getTileCoordsUnderCursor(d_session.getCamera());
  if (d_isMutliremoving && d_lastRemovedCoords && *d_lastRemovedCoords == tileCoords)
    return;

  ObjectsSpawner::despawnStructure(
    SAFE_DEREF(d_session.getLocation()),
    tileCoords,
    structure->getPrototype().layer);

  if (d_isMutliremoving)
    d_lastRemovedCoords = tileCoords;
}
