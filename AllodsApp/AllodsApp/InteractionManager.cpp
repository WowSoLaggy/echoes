#include "stdafx.h"
#include "InteractionManager.h"

#include "ItemPicker.h"
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

  if (const auto entityPtr = ItemPicker(d_session).pick())
  {
    if (const auto behaviorModel = entityPtr->getBehaviorModel())
    {
      behaviorModel->interact();
      return true;
    }
  }

  return false;
}
