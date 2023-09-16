#include "stdafx.h"
#include "GuiManager.h"

#include "Game.h"

#include <LaggyDx/App.h>
#include <LaggyDx/Button.h>
#include <LaggyDx/IResourceController.h>
#include <LaggyDx/Label.h>
#include <LaggyDx/Layout.h>
#include <LaggyDx/Panel.h>


namespace
{
  const std::string defaultFont = "MyFont.spritefont";

  const Dx::ITexture& getTexture(const fs::path& i_path)
  {
    const auto& rc = Dx::App::get().getResourceController();
    return rc.getTexture(i_path);
  }

  const Sdk::Vector2I& getResolution()
  {
    const auto& rd = Dx::App::get().getRenderDevice();
    return rd.getResolution();
  }

  Dx::Layout& createLayout(Dx::IControl& i_parent)
  {
    auto ctrl = std::make_shared<Dx::Layout>();
    i_parent.addChild(ctrl);
    return *ctrl;
  }

  Dx::Panel& createPanel(Dx::IControl& i_parent)
  {
    auto ctrl = std::make_shared<Dx::Panel>();
    i_parent.addChild(ctrl);
    return *ctrl;
  }

  Dx::Label& createLabel(Dx::IControl& i_parent)
  {
    auto ctrl = std::make_shared<Dx::Label>();
    i_parent.addChild(ctrl);
    ctrl->setFont(defaultFont);
    return *ctrl;
  }

  Dx::Button& createButton(Dx::IControl& i_parent)
  {
    auto ctrl = std::make_shared<Dx::Button>();
    i_parent.addChild(ctrl);
    ctrl->setFont(defaultFont);
    ctrl->setTextureName(Dx::ButtonState::Normal, "Button.png");
    ctrl->setTextureName(Dx::ButtonState::Hover, "ButtonLight.png");
    ctrl->setTextureName(Dx::ButtonState::Pressed, "ButtonPressed.png");
    return *ctrl;
  }

} // anonym NS


GuiManager::GuiManager(Game& i_game)
  : d_game(i_game)
{
}


void GuiManager::showLoadingScreen()
{
  auto& background = createPanel(d_game.getForm());
  background.setTexture(getTexture("Black.png"));
  background.setSize(getResolution().getVector<float>());

  auto& layout = createLayout(d_game.getForm());
  layout.setSize(getResolution().getVector<float>());
  layout.setAlign(Dx::LayoutAlign::TopToBottom_Center);

  auto& loadingLabel = createLabel(layout);
  loadingLabel.setText("Loading...");
}

void GuiManager::hideLoadingScreen()
{
  d_game.getForm().removeChildren();
}


void GuiManager::createMainMenu()
{
  auto& background = createPanel(d_game.getForm());
  background.setTexture(getTexture("Black.png"));
  background.setSize(getResolution().getVector<float>());

  auto& layout = createLayout(d_game.getForm());
  layout.setSize(getResolution().getVector<float>());
  layout.setAlign(Dx::LayoutAlign::TopToBottom_Center);
  layout.setOffsetBetweenElements(16);

  {
    auto& btn = createButton(layout);
    btn.setText("New Game");
    btn.setOnPress(std::bind(&Game::onNewGame, &d_game));
  }

  {
    auto& btn = createButton(layout);
    btn.setText("Exit");
    btn.setOnPress(std::bind(&Game::onExit, &d_game));
  }
}

void GuiManager::hideMainMenu()
{
  d_game.getForm().removeChildren();
}
