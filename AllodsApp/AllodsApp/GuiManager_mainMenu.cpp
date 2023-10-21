#include "stdafx.h"
#include "GuiManager.h"

#include "Game.h"
#include "GuiCreator.h"

#include <LaggyDx/Button.h>
#include <LaggyDx/Layout.h>
#include <LaggyDx/Panel.h>
#include <LaggyDx/TextureUtils.h>


void GuiManager::showMainMenu()
{
  auto& background = GuiCreator::createPanel(d_game.getForm());
  background.setTexture(Dx::TextureUtils::getTexture("Black.png"));
  background.setSize(getResolution());

  auto& layout = GuiCreator::createLayout(d_game.getForm());
  layout.setSize(getResolution());
  layout.setAlign(Dx::LayoutAlign::TopToBottom_Center);

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Start New Game");
    btn.setOnPress(std::bind(&Game::newSession, &d_game));
  }

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Load Game");
    btn.setOnPress(std::bind(&Game::loadSession, &d_game));
  }

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Exit to Desktop");
    btn.setOnPress(std::bind(&Game::closeApplication, &d_game));
  }
}

void GuiManager::hideMainMenu()
{
  d_game.getForm().removeChildren();
}
