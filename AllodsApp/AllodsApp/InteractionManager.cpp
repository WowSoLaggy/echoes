#include "stdafx.h"
#include "InteractionManager.h"

#include "CtxMenuContent.h"
#include "InteractionManagerEvents.h"
#include "ItemPicker.h"
#include "Session.h"
#include "Structure.h"


InteractionManager::InteractionManager(Session& i_session)
  : d_session(i_session)
{
}


bool InteractionManager::onMouseClick(const Dx::MouseKey i_key)
{
  if (i_key == Dx::MouseKey::Left)
  {
    if (d_isContextMenuShown)
      return hideContextMenu();
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
  const auto entityPtr = ItemPicker(d_session).pick();
  if (entityPtr == nullptr)
    return hideContextMenu();
  
  d_isContextMenuShown = true;
  notify(ShowCtxMenuEvent(CtxMenuContent(*entityPtr, d_session.isDevMode())));

  return true;
}

bool InteractionManager::hideContextMenu()
{
  if (!d_isContextMenuShown)
    return false;

  d_isContextMenuShown = false;
  notify(HideCtxMenuEvent());

  return true;
}
