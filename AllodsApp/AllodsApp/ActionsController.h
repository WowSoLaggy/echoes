#pragma once

#include "Fwd.h"
#include "OverlayTypes.h"

#include <LaggyDx/ActionsMap.h>

#include <LaggySdk/EventHandler.h>


class ActionsController : public Sdk::EventHandler
{
public:
  ActionsController(Game& i_game);

  virtual void processEvent(const Sdk::IEvent& i_event) override;

private:
  Game& d_game;

  void onSessionAttached(Session& i_session);
  void onSessionDetached(Session& i_session);
  void onDevModeSwitch(bool i_enabled);

  void setMainMenuActions();
  Dx::ActionsMap getCommonActions();
  void setDevModeActions();
  void setLiveModeActions();

  void setOnPress(Dx::ActionsMap& i_map, Dx::KeyboardKey i_key, auto i_func);

  void switchOverlay(OverlayType i_type);

  // ACTIONS

  void escapePress();

  void enableDevMode();
  void disableDevMode();

  void switchDevBuildMenu();

  void switchTempOverlay();
  void switchAtmoOverlay();

  void rotateDraftClockWise();
};
