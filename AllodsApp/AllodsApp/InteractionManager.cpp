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
    if (d_isCtxMenuShown)
      return hideCtxMenu();
    else
      return tryInteract();
  }
  else if (i_key == Dx::MouseKey::Right)
    return showCtxMenu();

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

bool InteractionManager::showCtxMenu()
{
  const auto entityPtr = ItemPicker(d_session).pick();
  if (entityPtr == nullptr)
    return hideCtxMenu();
  
  d_isCtxMenuShown = true;
  notify(ShowCtxMenuEvent(CtxMenuContent(*entityPtr, d_session.isDevMode())));

  return true;
}

bool InteractionManager::hideCtxMenu()
{
  if (!d_isCtxMenuShown)
    return false;

  d_isCtxMenuShown = false;
  notify(HideCtxMenuEvent());

  return true;
}
