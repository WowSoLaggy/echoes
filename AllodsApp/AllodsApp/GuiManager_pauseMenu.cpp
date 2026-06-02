#include "stdafx.h"
#include "GuiManager.h"

#include "Game.h"
#include "GuiCreator.h"
#include "Session.h"

#include <LaggyDx/Button.h>
#include <LaggyDx/Colors.h>
#include <LaggyDx/Layout.h>
#include <LaggyDx/Panel.h>


void GuiManager::showPauseMenu()
{
  CONTRACT_EXPECT(!d_pauseMenuPanel);

  d_pauseMenuPanel = &GuiCreator::createPanel(d_game.getForm());
  d_pauseMenuPanel->sendToFront();
  d_pauseMenuPanel->setTexture("Black.png");
  d_pauseMenuPanel->setSize(getResolution());
  d_pauseMenuPanel->setColor(Dx::colorWithAlpha(Dx::Colors::White, 0.5f));

  auto& layout = GuiCreator::createLayout(*d_pauseMenuPanel);
  layout.setSize(d_pauseMenuPanel->getSize());
  layout.setAlign(Dx::LayoutAlign::TopToBottom_Center);

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Resume Game");
    btn.setOnPress(std::bind(&GuiManager::onResumeGame, this));
  }

  GuiCreator::createFakePanel(layout);

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Save Game");
    btn.setOnPress(std::bind(&Game::saveSession, &d_game));
  }

  GuiCreator::createFakePanel(layout);

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Exit to Menu");
    btn.setOnPress(std::bind(&GuiManager::onExitToMenu, this));
  }

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Exit to Desktop");
    btn.setOnPress(std::bind(&Game::closeApplication, &d_game));
  }
}

void GuiManager::hidePauseMenu()
{
  CONTRACT_EXPECT(d_pauseMenuPanel);
  d_pauseMenuPanel->setParent(nullptr);
  d_pauseMenuPanel = nullptr;
}


void GuiManager::onResumeGame()
{
  CONTRACT_EXPECT(d_session);
  d_session->unpause();
}

void GuiManager::onExitToMenu()
{
  hidePauseMenu();
  d_game.closeSession();
}
