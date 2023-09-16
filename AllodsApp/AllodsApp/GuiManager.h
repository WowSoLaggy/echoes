#pragma once

#include <LaggyDx/LaggyDxFwd.h>


class GuiManager
{
public:
  GuiManager(Dx::IControl& i_rootControl);

  void showLoadingScreen();
  void hideLoadingScreen();
  void createMainMenu();

private:
  Dx::IControl& d_rootControl;
};
