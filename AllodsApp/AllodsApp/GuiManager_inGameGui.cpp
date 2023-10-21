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

  const bool devMode = SAFE_DEREF(d_session).isDevMode();

  auto& devModeLayout = GuiCreator::createLayout(*d_inGameGui);
  devModeLayout.setPosition({ 0, getResolution().y });
  devModeLayout.setAlign(Dx::LayoutAlign::LeftToRight_BottomSide);

  {
    auto& btn = GuiCreator::createButton(devModeLayout);
    btn.setTextureName(devMode ? "f1_enabled.png" : "f1_disabled.png");
    if (!devMode)
      btn.setOnPress(std::bind(&GuiManager::onBtnDevMode, this));
  }

  {
    auto& btn = GuiCreator::createButton(devModeLayout);
    btn.setTextureName(devMode ? "f2_disabled.png" : "f2_enabled.png");
    if (devMode)
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
  hideDevBuildMenu();
  hideCtxMenu();

  d_inGameGui->setParent(nullptr);
  d_inGameGui = nullptr;
}


void GuiManager::onBtnDevMode()
{
  CONTRACT_EXPECT(d_session);
  d_session->enableDevMode();
}

void GuiManager::onBtnLiveMode()
{
  CONTRACT_EXPECT(d_session);
  d_session->disableDevMode();
}
