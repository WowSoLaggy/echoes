#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>


class GuiManager
{
public:
  GuiManager(Game& i_game);

  void showLoadingScreen();
  void hideLoadingScreen();
  void createMainMenu();
  void hideMainMenu();

private:
  Game& d_game;
};
