#include "stdafx.h"
#include "BuildManager.h"

#include "BuildDraftInfo.h"
#include "ItemPicker.h"
#include "Mount.h"
#include "MountBuilder.h"
#include "Object.h"
#include "ObjectBuilder.h"
#include "ObjectsSpawner.h"
#include "Prototypes.h"
#include "PrototypeUtils.h"
#include "Session.h"
#include "SessionEvents.h"
#include "Structure.h"
#include "StructureBuilder.h"
#include "TileUtils.h"

#include <LaggyDx/App.h>
#include <LaggyDx/CursorUtils.h>


BuildManager::BuildManager(Session& i_session)
  : d_session(i_session)
{
}


bool BuildManager::isInBuildMode() const
{
  return d_buildPrototype.get();
}

void BuildManager::setBuildDraft(PrototypePtr i_prototype)
{
  stopRemovalMode();

  d_buildPrototype = i_prototype;
  createBuildDraftInfo();
  updateBuildDraft();

  notify(BuildDraftSetEvent(d_buildDraftInfo));
}

void BuildManager::resetBuildDraft()
{
  notify(BuildDraftSetEvent(nullptr));
  d_buildPrototype.reset();
  d_buildDraftInfo.reset();
}

void BuildManager::createBuildDraftInfo()
{
  CONTRACT_ASSERT(d_buildPrototype);
  if (isDraftMount())
    d_buildDraftInfo = std::make_shared<BuildMountDraftInfo>();
  else if (isDraftObject())
    d_buildDraftInfo = std::make_shared<BuildObjectDraftInfo>();
  else
    d_buildDraftInfo = std::make_shared<BuildDraftInfo>();

  CONTRACT_ENSURE(d_buildDraftInfo);
  d_buildDraftInfo->texture = d_buildPrototype->texture;
}


void BuildManager::rotateDraftClockwise()
{
  if (isDraftMount())
  {
    getDraftMount().fixtureLocation = rotateClockWise(getDraftMount().fixtureLocation);
    updateBuildDraft();
  }
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
    if (!isDraftObject())
    {
      // No objects spamming
      d_isMutlibuilding = true;
    }

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
  if (isDraftStructure())
    buildStructure();
  else if (isDraftMount())
    buildMount();
  else if (isDraftObject())
    buildObject();
  else
  {
    CONTRACT_THROW();
  }

  updateBuildAllowance();
}

void BuildManager::buildStructure()
{
  StructureBuilder(
    SAFE_DEREF(d_session.getCurrentLocation()), SAFE_DEREF(d_buildDraftInfo).tileCoords,
    d_buildPrototype).build();
}

void BuildManager::buildMount()
{
  MountBuilder(
    SAFE_DEREF(d_session.getCurrentLocation()), SAFE_DEREF(d_buildDraftInfo).tileCoords,
    d_buildPrototype, getDraftMount().fixtureLocation).build();
}

void BuildManager::buildObject()
{
  ObjectBuilder(
    SAFE_DEREF(d_session.getCurrentLocation()), getDraftObject().absCoords,
    d_buildPrototype).build();
}


bool BuildManager::isDraftStructure() const
{
  return dynamic_cast<const StructurePrototype*>(d_buildPrototype.get());
}

bool BuildManager::isDraftMount() const
{
  return dynamic_cast<const MountPrototype*>(d_buildPrototype.get());
}

bool BuildManager::isDraftObject() const
{
  return dynamic_cast<const ObjectPrototype*>(d_buildPrototype.get());
}

BuildMountDraftInfo& BuildManager::getDraftMount() const
{
  return SAFE_DEREF(dynamic_cast<BuildMountDraftInfo*>(d_buildDraftInfo.get()));
}

BuildObjectDraftInfo& BuildManager::getDraftObject() const
{
  return SAFE_DEREF(dynamic_cast<BuildObjectDraftInfo*>(d_buildDraftInfo.get()));
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
  
  if (isDraftObject())
    getDraftObject().absCoords = TileUtils::getAbsPosUnderCursor(d_session.getCamera());
}

void BuildManager::updateBuildAllowance()
{
  SAFE_DEREF(d_buildDraftInfo).allowed = canBeBuilt();
}

bool BuildManager::canBeBuilt() const
{
  if (isDraftStructure())
    return canBeBuiltStructure();
  else if (isDraftMount())
    return canBeBuiltMount();
  else if (isDraftObject())
    return canBeBuiltObject();
  
  CONTRACT_THROW();
}

bool BuildManager::canBeBuiltStructure() const
{
  return StructureBuilder(
    SAFE_DEREF(d_session.getCurrentLocation()), SAFE_DEREF(d_buildDraftInfo).tileCoords,
    d_buildPrototype).canBeBuilt();
}

bool BuildManager::canBeBuiltMount() const
{
  return MountBuilder(
    SAFE_DEREF(d_session.getCurrentLocation()), SAFE_DEREF(d_buildDraftInfo).tileCoords,
    d_buildPrototype, getDraftMount().fixtureLocation).canBeBuilt();
}

bool BuildManager::canBeBuiltObject() const
{
  return ObjectBuilder(
    SAFE_DEREF(d_session.getCurrentLocation()), getDraftObject().absCoords,
    d_buildPrototype).canBeBuilt();
}


void BuildManager::tryRemove()
{
  const auto entityPtr = ItemPicker(d_session).pick();
  if (!entityPtr)
    return;

  const auto tileCoords = TileUtils::getTileCoordsUnderCursor(d_session.getCamera());
  if (d_isMutliremoving && d_lastRemovedCoords && *d_lastRemovedCoords == tileCoords)
    return;

  if (const auto* structure = dynamic_cast<const Structure*>(entityPtr.get()))
  {
    ObjectsSpawner::despawnStructure(
      SAFE_DEREF(d_session.getCurrentLocation()),
      tileCoords,
      structure->getStructurePrototype().layer);
  }
  else if (const auto* mount = dynamic_cast<const Mount*>(entityPtr.get()))
  {
    ObjectsSpawner::despawnMount(
      SAFE_DEREF(d_session.getCurrentLocation()),
      tileCoords,
      *mount);
  }
  else if (const auto* object = dynamic_cast<const Object*>(entityPtr.get()))
  {
    ObjectsSpawner::despawnObject(
      SAFE_DEREF(d_session.getCurrentLocation()),
      *object);
  }

  if (d_isMutliremoving)
    d_lastRemovedCoords = tileCoords;
}
