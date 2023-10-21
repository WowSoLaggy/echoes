#include "stdafx.h"
#include "GuiManager.h"

#include "Game.h"
#include "GuiCreator.h"

#include <LaggyDx/Label.h>
#include <LaggyDx/Layout.h>
#include <LaggyDx/Panel.h>
#include <LaggyDx/TextureUtils.h>


void GuiManager::showLoadingScreen()
{
  d_background = &GuiCreator::createPanel(d_game.getForm());
  d_background->setTexture(Dx::TextureUtils::getTexture("Black.png"));
  d_background->setSize(getResolution());

  auto& layout = GuiCreator::createLayout(*d_background);
  layout.setSize(getResolution());
  layout.setAlign(Dx::LayoutAlign::TopToBottom_Center);

  auto& loadingLabel = GuiCreator::createLabel(layout);
  loadingLabel.setText("Loading...");
}

void GuiManager::hideLoadingScreen()
{
  CONTRACT_EXPECT(d_background);

  d_background->setParent(nullptr);
  d_background = nullptr;
}
