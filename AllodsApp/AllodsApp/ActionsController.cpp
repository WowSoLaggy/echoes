#include "stdafx.h"
#include "ActionsController.h"

#include "Game.h"
#include "Session.h"
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
  i_enabled ? setGodModeActions() : setLiveModeActions();
}


void ActionsController::setMainMenuActions()
{
  d_game.setActionsMap(Dx::ActionsMap());
}

Dx::ActionsMap ActionsController::getCommonActions()
{
  Dx::ActionsMap actions;

  setOnPress(actions, Dx::KeyboardKey::Escape, &ActionsController::escapePress);

  return actions;
}

void ActionsController::setGodModeActions()
{
  auto actions = getCommonActions();

  setOnPress(actions, Dx::KeyboardKey::F2, &ActionsController::disableGodMode);

  setOnPress(actions, Dx::KeyboardKey::B, &ActionsController::switchGodModeBuildMenu);

  setOnPress(actions, Dx::KeyboardKey::F5, &ActionsController::switchTempOverlay);
  setOnPress(actions, Dx::KeyboardKey::F6, &ActionsController::switchAtmoOverlay);

  setOnPress(actions, Dx::KeyboardKey::R, &ActionsController::rotateDraftClockWise);

  d_game.setActionsMap(std::move(actions));
}


void ActionsController::setLiveModeActions()
{
  auto actions = getCommonActions();

  setOnPress(actions, Dx::KeyboardKey::F1, &ActionsController::enableGodMode);

  d_game.setActionsMap(std::move(actions));
}


void ActionsController::setOnPress(Dx::ActionsMap& i_map, const Dx::KeyboardKey i_key, auto i_func)
{
  i_map.setAction(i_key, std::bind(i_func, this), Dx::ActionType::OnPress);
}


void ActionsController::escapePress()
{
  SAFE_DEREF(d_game.getSession()).onEscape();
}

void ActionsController::enableGodMode()
{
  SAFE_DEREF(d_game.getSession()).enableGodMode();
}

void ActionsController::disableGodMode()
{
  SAFE_DEREF(d_game.getSession()).disableGodMode();
}


void ActionsController::switchGodModeBuildMenu()
{
  if (d_game.getGui().isGodModeBuildMenuShown())
    d_game.getGui().hideGodModeBuildMenu();
  else
    d_game.getGui().showGodModeBuildMenu();
}


void ActionsController::switchOverlay(const OverlayType i_type)
{
  auto& session = SAFE_DEREF(d_game.getSession());
  if (const auto* overlay = session.getOverlay(); overlay && overlay->getType() == i_type)
    session.resetOverlay();
  else
    session.setOverlay(i_type);
}

void ActionsController::switchTempOverlay()
{
  switchOverlay(OverlayType::Temp);
}

void ActionsController::switchAtmoOverlay()
{
  switchOverlay(OverlayType::Atmo);
}


void ActionsController::rotateDraftClockWise()
{
  auto& session = SAFE_DEREF(d_game.getSession());
  session.getBuildManger().rotateDraftClockwise();
}
