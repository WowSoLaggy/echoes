#include "stdafx.h"
#include "ActionsController.h"

#include "Game.h"
#include "SessionEvents.h"


ActionsController::ActionsController(Game& i_game)
  : d_game(i_game)
{
  connectTo(d_game);
}


void ActionsController::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const SessionAttachedEvent*>(&i_event))
    onSessionAttached(event->getSession());
  else if (const auto* event = dynamic_cast<const SessionDetachedEvent*>(&i_event))
    onSessionDetached(event->getSession());
  else if (const auto* event = dynamic_cast<const GodModeEvent*>(&i_event))
    onGodMode(event->getEnabled());
}


void ActionsController::onSessionAttached(Session& i_session)
{
  onGodMode(i_session.isGodMode());
  connectTo(i_session);
}

void ActionsController::onSessionDetached(Session& i_session)
{
  disconnectFrom(i_session);
  setMainMenuActions();
}

void ActionsController::onGodMode(const bool i_enabled)
{
  i_enabled ? setGodModeActions() : setInGameActions();
}


void ActionsController::setMainMenuActions()
{
  d_game.setActionsMap(Dx::ActionsMap());
}

void ActionsController::setGodModeActions()
{
  Dx::ActionsMap actions;

  actions.setAction(Dx::KeyboardKey::F2, Dx::Action(std::bind(&ActionsController::disableGodMode, this)), Dx::ActionType::OnPress);

  actions.setAction(Dx::KeyboardKey::B, Dx::Action(std::bind(&ActionsController::switchGodModeBuildMenu, this)), Dx::ActionType::OnPress);

  d_game.setActionsMap(std::move(actions));
}


void ActionsController::setInGameActions()
{
  Dx::ActionsMap actions;

  actions.setAction(Dx::KeyboardKey::F1, Dx::Action(std::bind(&ActionsController::enableGodMode, this)), Dx::ActionType::OnPress);

  d_game.setActionsMap(std::move(actions));
}


void ActionsController::enableGodMode()
{
  auto* session = d_game.getSession();
  CONTRACT_EXPECT(session);
  session->enableGodMode();
}

void ActionsController::disableGodMode()
{
  auto* session = d_game.getSession();
  CONTRACT_EXPECT(session);
  session->disableGodMode();
}


void ActionsController::switchGodModeBuildMenu()
{
  if (d_game.getGui().isGodModeBuildMenuShown())
    d_game.getGui().hideGodModeBuildMenu();
  else
    d_game.getGui().showGodModeBuildMenu();
}
