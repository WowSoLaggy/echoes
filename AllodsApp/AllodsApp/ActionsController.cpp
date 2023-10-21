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
  else if (const auto* event = dynamic_cast<const DevModeSwitchEvent*>(&i_event))
    onDevModeSwitch(event->getEnabled());
}


void ActionsController::onSessionAttached(Session& i_session)
{
  onDevModeSwitch(i_session.isDevMode());
  connectTo(i_session);
}

void ActionsController::onSessionDetached(Session& i_session)
{
  disconnectFrom(i_session);
  setMainMenuActions();
}

void ActionsController::onDevModeSwitch(const bool i_enabled)
{
  i_enabled ? setDevModeActions() : setLiveModeActions();
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

void ActionsController::setDevModeActions()
{
  auto actions = getCommonActions();

  setOnPress(actions, Dx::KeyboardKey::F2, &ActionsController::disableDevMode);

  setOnPress(actions, Dx::KeyboardKey::B, &ActionsController::switchDevBuildMenu);

  setOnPress(actions, Dx::KeyboardKey::F5, &ActionsController::switchTempOverlay);
  setOnPress(actions, Dx::KeyboardKey::F6, &ActionsController::switchAtmoOverlay);

  setOnPress(actions, Dx::KeyboardKey::R, &ActionsController::rotateDraftClockWise);

  d_game.setActionsMap(std::move(actions));
}


void ActionsController::setLiveModeActions()
{
  auto actions = getCommonActions();

  setOnPress(actions, Dx::KeyboardKey::F1, &ActionsController::enableDevMode);

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

void ActionsController::enableDevMode()
{
  SAFE_DEREF(d_game.getSession()).enableDevMode();
}

void ActionsController::disableDevMode()
{
  SAFE_DEREF(d_game.getSession()).disableDevMode();
}


void ActionsController::switchDevBuildMenu()
{
  if (d_game.getGui().isDevBuildMenuShown())
    d_game.getGui().hideDevBuildMenu();
  else
    d_game.getGui().showDevBuildMenu();
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
