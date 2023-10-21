#include "stdafx.h"
#include "GuiManager.h"

#include "Game.h"
#include "GuiCreator.h"
#include "Session.h"

#include <LaggyDx/Button.h>
#include <LaggyDx/Layout.h>


void GuiManager::recreateInGameGui()
{
  hideInGameGui();
  showInGameGui();
}

void GuiManager::showInGameGui()
{
  CONTRACT_EXPECT(!d_inGameGui);

  d_inGameGui = &GuiCreator::createControl(d_game.getForm());

  const bool godMode = SAFE_DEREF(d_session).isGodMode();

  auto& godModeLayout = GuiCreator::createLayout(*d_inGameGui);
  godModeLayout.setPosition({ 0, (float)getResolution().y });
  godModeLayout.setAlign(Dx::LayoutAlign::LeftToRight_BottomSide);

  {
    auto& btn = GuiCreator::createButton(godModeLayout);
    btn.setTextureName(godMode ? "f1_enabled.png" : "f1_disabled.png");
    if (!godMode)
      btn.setOnPress(std::bind(&GuiManager::onBtnGodMode, this));
  }

  {
    auto& btn = GuiCreator::createButton(godModeLayout);
    btn.setTextureName(godMode ? "f2_disabled.png" : "f2_enabled.png");
    if (godMode)
      btn.setOnPress(std::bind(&GuiManager::onBtnLiveMode, this));
  }

  d_overlay = d_session->getOverlay();
  if (d_overlay)
    showOverlayUI();
}

void GuiManager::hideInGameGui()
{
  CONTRACT_EXPECT(d_inGameGui);

  hideOverlayUI();
  hideGodModeBuildMenu();
  hideCtxMenu();

  d_inGameGui->setParent(nullptr);
  d_inGameGui = nullptr;
}


void GuiManager::onBtnGodMode()
{
  CONTRACT_EXPECT(d_session);
  d_session->enableGodMode();
}

void GuiManager::onBtnLiveMode()
{
  CONTRACT_EXPECT(d_session);
  d_session->disableGodMode();
}
