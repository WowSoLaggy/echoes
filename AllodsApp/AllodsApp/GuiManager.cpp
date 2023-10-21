#include "stdafx.h"
#include "GuiManager.h"

#include "Game.h"
#include "GameEvents.h"
#include "InteractionManagerEvents.h"
#include "Session.h"
#include "SessionEvents.h"


GuiManager::GuiManager(Game& i_game)
  : d_game(i_game)
{
  connectTo(d_game);
}


void GuiManager::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const GameStateChangedEvent*>(&i_event))
    onGameStateChanged(event->getNewState());

  else if (const auto* event = dynamic_cast<const SessionAttachedEvent*>(&i_event))
    onSessionAttached(event->getSession());
  else if (const auto* event = dynamic_cast<const SessionDetachedEvent*>(&i_event))
    onSessionDetached(event->getSession());
  
  else if (const auto* event = dynamic_cast<const DevModeSwitchEvent*>(&i_event))
    onDevModeSwitchEvent(event->getEnabled());
  
  else if (const auto* event = dynamic_cast<const PauseEvent*>(&i_event))
    showPauseMenu();
  else if (const auto* event = dynamic_cast<const UnpauseEvent*>(&i_event))
    hidePauseMenu();
  
  else if (const auto* event = dynamic_cast<const ExitBuildRemovalEvent*>(&i_event))
    onExitBuildRemoval();
  
  else if (const auto* event = dynamic_cast<const OverlaySetEvent*>(&i_event))
    onOverlaySet(event->getOverlay());

  else if (const auto* event = dynamic_cast<const ShowCtxMenuEvent*>(&i_event))
    showCtxMenu(event->getCtxMenuContent());
  else if (const auto* event = dynamic_cast<const HideCtxMenuEvent*>(&i_event))
    hideCtxMenu();
}


void GuiManager::update()
{
  if (!d_session || d_session->isPause())
    return;

  if (d_overlayHint)
    updateOverlayHint();
}


Sdk::Vector2F GuiManager::getResolution() const
{
  const auto& rd = Dx::App::get().getRenderDevice();
  return rd.getResolution().getVector<float>();
}


void GuiManager::onSessionAttached(Session& i_session)
{
  CONTRACT_ASSERT(!d_session);

  d_session = &i_session;
  connectTo(i_session);
  connectTo(i_session.getInteractionManger());
  
  hideMainMenu();
  showInGameGui();
}

void GuiManager::onSessionDetached(Session& i_session)
{
  hideInGameGui();

  disconnectFrom(i_session);
  d_session = nullptr;

  showMainMenu();
}


void GuiManager::onDevModeSwitchEvent(bool i_enabled)
{
  i_enabled ? onDevModeOn() : onDevModeOff();
}

void GuiManager::onDevModeOn()
{
  recreateInGameGui();
}

void GuiManager::onDevModeOff()
{
  recreateInGameGui();
  hideDevBuildMenu();
}


void GuiManager::onGameStateChanged(const GameState i_newState)
{
  if (i_newState == GameState::Loading)
    showLoadingScreen();
  else if (i_newState == GameState::Loaded)
  {
    hideLoadingScreen();
    showMainMenu();
  }
}
