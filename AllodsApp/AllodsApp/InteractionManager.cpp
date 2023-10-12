#include "stdafx.h"
#include "InteractionManager.h"

#include "EntityUtils.h"
#include "Session.h"
#include "Structure.h"


InteractionManager::InteractionManager(Session& i_session)
  : d_session(i_session)
{
}


bool InteractionManager::onMouseClick(Dx::MouseKey i_key)
{
  if (i_key != Dx::MouseKey::Left)
    return false;

  if (const auto entityPtr = EntityUtils::getEntityUnderCursor(d_session))
  {
    if (const auto behaviorModel = entityPtr->getBehaviorModel())
    {
      behaviorModel->interact();
      return true;
    }
  }

  return false;
}
