#include "stdafx.h"
#include "ActionsController.h"

#include "Game.h"


ActionsController::ActionsController(Game& i_game)
  : d_game(i_game)
{
}


void ActionsController::setInGameActions()
{
  Dx::ActionsMap actions;

  actions.setAction(Dx::KeyboardKey::F1, Dx::Action(std::bind(&ActionsController::onEnableGodMode, this)), Dx::ActionType::OnPress);
  actions.setAction(Dx::KeyboardKey::F2, Dx::Action(std::bind(&ActionsController::onDisableGodMode, this)), Dx::ActionType::OnPress);

  d_game.setActionsMap(std::move(actions));
}


void ActionsController::onEnableGodMode()
{
  auto* session = d_game.getSession();
  CONTRACT_EXPECT(session);
  session->enableGodMode();
}

void ActionsController::onDisableGodMode()
{
  auto* session = d_game.getSession();
  CONTRACT_EXPECT(session);
  session->disableGodMode();
}
