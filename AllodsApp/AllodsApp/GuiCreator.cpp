#include "stdafx.h"
#include "GuiCreator.h"

#include "CtxMenu.h"
#include "Fonts.h"

#include <LaggyDx/Button.h>
#include <LaggyDx/Grid.h>
#include <LaggyDx/GridItem.h>
#include <LaggyDx/Label.h>
#include <LaggyDx/Layout.h>
#include <LaggyDx/Panel.h>


Dx::Control& GuiCreator::createControl(Dx::IControl& i_parent)
{
  auto ctrl = std::make_shared<Dx::Control>();
  i_parent.addChild(ctrl);
  return *ctrl;
}

Dx::Layout& GuiCreator::createLayout(Dx::IControl& i_parent)
{
  auto ctrl = std::make_shared<Dx::Layout>();
  i_parent.addChild(ctrl);
  ctrl->setOffsetBetweenElements(16);
  return *ctrl;
}

Dx::Panel& GuiCreator::createPanel(Dx::IControl& i_parent)
{
  auto ctrl = std::make_shared<Dx::Panel>();
  i_parent.addChild(ctrl);
  return *ctrl;
}

Dx::Label& GuiCreator::createLabel(Dx::IControl& i_parent)
{
  auto ctrl = std::make_shared<Dx::Label>();
  i_parent.addChild(ctrl);
  ctrl->setFont(Fonts::getMenuFont());
  return *ctrl;
}

Dx::Button& GuiCreator::createButton(Dx::IControl& i_parent)
{
  auto ctrl = std::make_shared<Dx::Button>();
  i_parent.addChild(ctrl);
  ctrl->setFont(Fonts::getMenuFont());
  return *ctrl;
}

Dx::Button& GuiCreator::createMenuButton(Dx::IControl& i_parent)
{
  auto& ctrl = createButton(i_parent);
  ctrl.setTextureName(Dx::ButtonState::Normal, "Button.png");
  ctrl.setTextureName(Dx::ButtonState::Hover, "ButtonLight.png");
  ctrl.setTextureName(Dx::ButtonState::Pressed, "ButtonPressed.png");
  return ctrl;
}

Dx::Button& GuiCreator::createCtxMenuButton(Dx::IControl& i_parent)
{
  auto& ctrl = createButton(i_parent);
  ctrl.setTextureName(Dx::ButtonState::Normal, "CtxButton.png");
  ctrl.setTextureName(Dx::ButtonState::Hover, "CtxButton.png");
  ctrl.setTextureName(Dx::ButtonState::Pressed, "CtxButtonPressed.png");
  return ctrl;
}

Dx::Grid& GuiCreator::createGrid(Dx::IControl& i_parent, const int i_slotsX, const int i_slotsY)
{
  auto ctrl = std::make_shared<Dx::Grid>(Sdk::Vector2I{ i_slotsX, i_slotsY });
  i_parent.addChild(ctrl);

  ctrl->setTextures(
    "Grid_T.png", "Grid_TL.png", "Grid_TR.png",
    "Grid_L.png", "Grid_R.png",
    "Grid_B.png", "Grid_BL.png", "Grid_BR.png",
    "Grid_Slot.png", "Grid_Selection.png");

  return *ctrl;
}


CtxMenu& GuiCreator::createCtxMenu(Dx::IControl& i_parent)
{
  auto ctrl = std::make_shared<CtxMenu>();
  i_parent.addChild(ctrl);
  return *ctrl;
}


void GuiCreator::createFakePanel(Dx::IControl& i_parent, const float i_height)
{
  auto& fakePanel = GuiCreator::createPanel(i_parent);
  fakePanel.setSize({ 0, i_height });
}
