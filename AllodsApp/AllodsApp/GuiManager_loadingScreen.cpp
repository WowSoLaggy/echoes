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
  auto& background = GuiCreator::createPanel(d_game.getForm());
  background.setTexture(Dx::TextureUtils::getTexture("Black.png"));
  background.setSize(getResolution().getVector<float>());

  auto& layout = GuiCreator::createLayout(d_game.getForm());
  layout.setSize(getResolution().getVector<float>());
  layout.setAlign(Dx::LayoutAlign::TopToBottom_Center);

  auto& loadingLabel = GuiCreator::createLabel(layout);
  loadingLabel.setText("Loading...");
}

void GuiManager::hideLoadingScreen()
{
  d_game.getForm().removeChildren();
}
