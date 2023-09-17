#pragma once

#include "Fwd.h"


class ActionsController
{
public:
  ActionsController(Game& i_game);

  void setInGameActions();

private:
  Game& d_game;

  void onEnableGodMode();
  void onDisableGodMode();
};
