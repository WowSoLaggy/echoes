#include "stdafx.h"
#include "GuiManager.h"

#include "CtxMenuContent.h"
#include "Fonts.h"
#include "Game.h"
#include "GuiCreator.h"

#include <LaggyDx/CursorUtils.h>
#include <LaggyDx/IFontResource.h>
#include <LaggyDx/Label.h>
#include <LaggyDx/Panel.h>
#include <LaggyDx/TextureUtils.h>


void GuiManager::showCtxMenu(const CtxMenuContent& i_ctxMenuContent)
{
  hideCtxMenu();

  d_ctxMenu = &GuiCreator::createPanel(d_game.getForm());
  d_ctxMenu->setTexture(Dx::TextureUtils::getTexture("White.png"));
  d_ctxMenu->setColor({ 0.6f, 0.47f, 0.31f, 0.8f });
  d_ctxMenu->setPosition(Dx::CursorUtils::getPosition().getVector<float>());

  auto& label = GuiCreator::createLabel(*d_ctxMenu);
  label.setFont(Fonts::getInGameHintsFont());
  label.setText(i_ctxMenuContent.getDescription());

  const auto stringRect = SAFE_DEREF(label.getFontResource()).getStringRect(label.getText());
  d_ctxMenu->setSize(stringRect.size().getVector<float>() + Sdk::Vector2F(4, 0));
}

void GuiManager::hideCtxMenu()
{
  if (d_ctxMenu)
  {
    d_ctxMenu->setParent(nullptr);
    d_ctxMenu = nullptr;
  }
}
