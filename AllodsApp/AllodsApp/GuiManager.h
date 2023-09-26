#pragma once

#include "Fwd.h"
#include "GameStates.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/EventHandler.h>


class GuiManager : public Sdk::EventHandler
{
public:
  GuiManager(Game& i_game);

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  bool isGodModeBuildMenuShown() const;
  void showGodModeBuildMenu();
  void hideGodModeBuildMenu();

private:
  Game& d_game;
  Session* d_session = nullptr;

  void onGameStateChanged(GameState i_newState);

  void showLoadingScreen();
  void hideLoadingScreen();
  void createMainMenu();
  void hideMainMenu();
  void createInGameMenu();

  Dx::RadioButton* d_rbF1 = nullptr;
  Dx::RadioButton* d_rbF2 = nullptr;
  void onCheck_rbF1();
  void onCheck_rbF2();

  Dx::Grid* d_godModeBuildGrid = nullptr;
  void onGodModeBuildSelectedItem(const Dx::GridItem& i_item);
  void onGodModeBuildUnselectedItem();

  void onSessionAttached(Session& i_session);
  void onSessionDetached(Session& i_session);

  Dx::Panel* d_pauseMenuPanel = nullptr;
  void showPauseMenu();
  void hidePauseMenu();
  
  void onGodModeEvent(bool i_enabled);

  void onExitBuildRemoval();

  void onResumeGame();
};
