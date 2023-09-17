#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/EventHandler.h>


class GuiManager : public Sdk::EventHandler
{
public:
  GuiManager(Game& i_game);
  ~GuiManager();

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  void showLoadingScreen();
  void hideLoadingScreen();

  void createMainMenu();
  void hideMainMenu();

  void createInGameMenu();

private:
  Game& d_game;
  Session* d_session = nullptr;

  Dx::RadioButton* d_rbF1 = nullptr;
  Dx::RadioButton* d_rbF2 = nullptr;
  void onCheck_rbF1();
  void onCheck_rbF2();

  void onSessionAttached(Session& i_session);
  void onSessionDetached(Session& i_session);
  void onGodModeEvent(bool i_enabled);
};
