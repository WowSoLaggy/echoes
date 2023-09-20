#include "stdafx.h"
#include "GuiManager.h"

#include "Game.h"
#include "GodModeBuildGridItems.h"
#include "SessionEvents.h"

#include <LaggyDx/App.h>
#include <LaggyDx/Button.h>
#include <LaggyDx/Grid.h>
#include <LaggyDx/IResourceController.h>
#include <LaggyDx/Label.h>
#include <LaggyDx/Layout.h>
#include <LaggyDx/Panel.h>
#include <LaggyDx/RadioButton.h>
#include <LaggyDx/RadioGroup.h>


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
    return *ctrl;
  }

  Dx::Button& createMenuButton(Dx::IControl& i_parent)
  {
    auto& ctrl = createButton(i_parent);
    ctrl.setTextureName(Dx::ButtonState::Normal, "Button.png");
    ctrl.setTextureName(Dx::ButtonState::Hover, "ButtonLight.png");
    ctrl.setTextureName(Dx::ButtonState::Pressed, "ButtonPressed.png");
    return ctrl;
  }

  Dx::RadioButton& createRadioButton(Dx::IControl& i_parent)
  {
    auto ctrl = std::make_shared<Dx::RadioButton>();
    i_parent.addChild(ctrl);
    return *ctrl;
  }

  Dx::RadioGroup& createRadioGroup(Dx::IControl& i_parent)
  {
    auto ctrl = std::make_shared<Dx::RadioGroup>();
    i_parent.addChild(ctrl);
    return *ctrl;
  }

  Dx::Grid& createGrid(Dx::IControl& i_parent, const int i_slotsX, const int i_slotsY)
  {
    auto ctrl = std::make_shared<Dx::Grid>(i_slotsX, i_slotsY);
    i_parent.addChild(ctrl);
    return *ctrl;
  }

} // anonym NS


GuiManager::GuiManager(Game& i_game)
  : d_game(i_game)
{
  connectTo(d_game);
}


void GuiManager::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const SessionAttachedEvent*>(&i_event))
    onSessionAttached(event->getSession());
  else if (const auto* event = dynamic_cast<const SessionDetachedEvent*>(&i_event))
    onSessionDetached(event->getSession());
  else if (const auto* event = dynamic_cast<const GodModeEvent*>(&i_event))
    onGodModeEvent(event->getEnabled());
}


void GuiManager::onSessionAttached(Session& i_session)
{
  d_session = &i_session;
  connectTo(i_session);
}

void GuiManager::onSessionDetached(Session& i_session)
{
  disconnectFrom(i_session);
  d_session = nullptr;
}

void GuiManager::onGodModeEvent(bool i_enabled)
{
  if (i_enabled)
    SAFE_DEREF(d_rbF1).check();
  else
    SAFE_DEREF(d_rbF2).check();
}


void GuiManager::onCheck_rbF1()
{
  CONTRACT_EXPECT(d_session);
  d_session->enableGodMode(true);
}

void GuiManager::onCheck_rbF2()
{
  CONTRACT_EXPECT(d_session);
  d_session->disableGodMode(true);
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
    auto& btn = createMenuButton(layout);
    btn.setText("New Game");
    btn.setOnPress(std::bind(&Game::onNewSession, &d_game));
  }

  {
    auto& btn = createMenuButton(layout);
    btn.setText("Exit");
    btn.setOnPress(std::bind(&Game::onCloseApplication, &d_game));
  }
}

void GuiManager::hideMainMenu()
{
  d_game.getForm().removeChildren();
}


void GuiManager::createInGameMenu()
{
  auto& rgModes = createRadioGroup(d_game.getForm());
  rgModes.setPosition({ 0, (float)getResolution().y });
  rgModes.setAlign(Dx::LayoutAlign::LeftToRight_BottomSide);

  d_rbF1 = &createRadioButton(rgModes);
  d_rbF1->setTextureName(Dx::RadioButtonState::Checked, "f1_enabled.png");
  d_rbF1->setTextureName(Dx::RadioButtonState::Unchecked, "f1_disabled.png");
  d_rbF1->setOnCheck(std::bind(&GuiManager::onCheck_rbF1, this));

  d_rbF2 = &createRadioButton(rgModes);
  d_rbF2->setTextureName(Dx::RadioButtonState::Checked, "f2_enabled.png");
  d_rbF2->setTextureName(Dx::RadioButtonState::Unchecked, "f2_disabled.png");
  d_rbF2->setOnCheck(std::bind(&GuiManager::onCheck_rbF2, this));
}


bool GuiManager::isGodModeBuildMenuShown() const
{
  return d_godModeBuildGrid;
}

void GuiManager::showGodModeBuildMenu()
{
  d_godModeBuildGrid = &createGrid(d_game.getForm(), 3, 2);
  d_godModeBuildGrid->setItems(getGodModeBuildGridItems());
}

void GuiManager::hideGodModeBuildMenu()
{
  if (d_godModeBuildGrid)
  {
    d_godModeBuildGrid->setParent(nullptr);
    d_godModeBuildGrid = nullptr;
  }
}
