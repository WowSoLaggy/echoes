#include "stdafx.h"
#include "GuiManager.h"

#include "CtxMenu.h"
#include "Game.h"
#include "GuiCreator.h"

#include <LaggyDx/CursorUtils.h>


void GuiManager::showCtxMenu(const CtxMenuContent& i_ctxMenuContent)
{
  hideCtxMenu();

  d_ctxMenu = &GuiCreator::createCtxMenu(d_game.getForm());
  d_ctxMenu->setContext(i_ctxMenuContent);
  d_ctxMenu->setPosition(Dx::CursorUtils::getPosition().getVector<float>());
}

void GuiManager::hideCtxMenu()
{
  if (d_ctxMenu)
  {
    d_ctxMenu->setParent(nullptr);
    d_ctxMenu = nullptr;
  }
}
