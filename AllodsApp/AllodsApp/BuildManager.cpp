#include "stdafx.h"
#include "BuildManager.h"

#include "BuildDraftInfo.h"
#include "SessionEvents.h"
#include "StructurePrototype.h"

#include <LaggyDx/App.h>


BuildManager::BuildManager(Session& i_session)
  : d_session(i_session)
{
}


void BuildManager::setBuildDraft(const StructurePrototype& i_prototype)
{
  d_buildPrototype = &i_prototype;
  d_buildDraftInfo = std::make_shared<BuildDraftInfo>(BuildDraftInfo(d_buildPrototype->textureName));
  updateBuildAllowance();

  notify(BuildDraftSetEvent(d_buildDraftInfo));
}

void BuildManager::resetBuildDraft()
{
  notify(BuildDraftSetEvent(nullptr));
  d_buildPrototype = nullptr;
  d_buildDraftInfo.reset();
}


void BuildManager::update()
{
  if (!d_buildDraftInfo)
    return;

  updateBuildPosition();
  updateBuildAllowance();
}


void BuildManager::updateBuildPosition()
{
  const auto& mousePos = Dx::App::get().getInputDevice().getMousePosition();
  SAFE_DEREF(d_buildDraftInfo).position = mousePos;
}

void BuildManager::updateBuildAllowance()
{
  SAFE_DEREF(d_buildDraftInfo).allowed = canBeBuilt();
}

bool BuildManager::canBeBuilt() const
{
  return true;
}
