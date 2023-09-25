#include "stdafx.h"
#include "InteractionManager.h"

#include "Session.h"
#include "Structure.h"
#include "StructureUtils.h"


InteractionManager::InteractionManager(Session& i_session)
  : d_session(i_session)
{
}


bool InteractionManager::onMouseClick(Dx::MouseKey i_key)
{
  if (i_key != Dx::MouseKey::Left)
    return false;

  if (const auto structurePtr = StructureUtils::getStructureUnderCursor(d_session))
  {
    if (const auto behaviorModel = structurePtr->getBehaviorModel())
    {
      behaviorModel->interact();
      return true;
    }
  }

  return false;
}
