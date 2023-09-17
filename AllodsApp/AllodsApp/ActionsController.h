#pragma once

#include "Fwd.h"

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
  void onGodMode(bool i_enabled);

  void setMainMenuActions();
  void setGodModeActions();
  void setInGameActions();

  // ACTIONS

  void enableGodMode();
  void disableGodMode();

  void showGodModeBuildMenu();
};
