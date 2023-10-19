#include "stdafx.h"
#include "InteractionManager.h"

#include "InteractionManagerEvents.h"
#include "ItemPicker.h"
#include "Session.h"
#include "Structure.h"


InteractionManager::InteractionManager(Session& i_session)
  : d_session(i_session)
{
}


bool InteractionManager::onMouseClick(Dx::MouseKey i_key)
{
  if (i_key == Dx::MouseKey::Left)
  {
    if (d_isContextMenuShown)
    {
      hideContextMenu();
      return true;
    }
    else
      return tryInteract();
  }
  else if (i_key == Dx::MouseKey::Right)
    return showContextMenu();

  return false;
}


bool InteractionManager::tryInteract()
{
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

bool InteractionManager::showContextMenu()
{
  const bool hasItemPicked = ItemPicker(d_session).pick() != nullptr;
  if (!hasItemPicked)
    return hideContextMenu();
  
  d_isContextMenuShown = true;
  notify(ShowContextMenuEvent());

  return true;
}

bool InteractionManager::hideContextMenu()
{
  if (!d_isContextMenuShown)
    return false;

  d_isContextMenuShown = false;
  notify(HideContextMenuEvent());

  return true;
}
