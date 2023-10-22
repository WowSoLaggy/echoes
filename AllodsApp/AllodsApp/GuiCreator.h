#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>


class GuiCreator
{
public:
  static Dx::Control& createControl(Dx::IControl& i_parent);
  static Dx::Layout& createLayout(Dx::IControl& i_parent);
  static Dx::Panel& createPanel(Dx::IControl& i_parent);
  static Dx::Label& createLabel(Dx::IControl& i_parent);
  static Dx::Button& createButton(Dx::IControl& i_parent);
  static Dx::Button& createMenuButton(Dx::IControl& i_parent);
  static Dx::Button& createCtxMenuButton(Dx::IControl& i_parent);
  static Dx::Grid& createGrid(Dx::IControl& i_parent, const int i_slotsX, const int i_slotsY);

  static CtxMenu& createCtxMenu(Dx::IControl& i_parent, InteractionManager& i_interactionManager);

  static void createFakePanel(Dx::IControl& i_parent, float i_height = 16);

private:
  GuiCreator() = delete;
};
