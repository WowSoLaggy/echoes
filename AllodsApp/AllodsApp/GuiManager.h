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

  void update();

  bool isDevBuildMenuShown() const;
  void showDevBuildMenu();
  void hideDevBuildMenu();

private:
  Game& d_game;
  Session* d_session = nullptr;

  void onGameStateChanged(GameState i_newState);

  Sdk::Vector2F getResolution() const;

  Dx::Panel* d_background = nullptr;
  void showLoadingScreen();
  void hideLoadingScreen();

  void showMainMenu();
  void hideMainMenu();
  void recreateInGameGui();
  void showInGameGui();
  void hideInGameGui();

  Dx::Control* d_inGameGui = nullptr;
  void onBtnDevMode();
  void onBtnLiveMode();

  Dx::Grid* d_devBuildGrid = nullptr;
  void onDevBuildSelectedItem(const Dx::GridItem& i_item);
  void onDevBuildUnselectedItem();

  void onSessionAttached(Session& i_session);
  void onSessionDetached(Session& i_session);

  Dx::Panel* d_pauseMenuPanel = nullptr;
  void showPauseMenu();
  void hidePauseMenu();
  
  void onDevModeSwitchEvent(bool i_enabled);
  void onDevModeOn();
  void onDevModeOff();

  void onExitBuildRemoval();

  void onResumeGame();
  void onExitToMenu();

  const IOverlay* d_overlay = nullptr;
  Dx::Panel* d_overlayPanel = nullptr;
  void onOverlaySet(const IOverlay* i_overlay);
  void showOverlayUI();
  void hideOverlayUI();
  Dx::Panel* d_overlayHint = nullptr;
  Dx::Label* d_overlayHintLabel = nullptr;
  void showOverlayHintTemp();
  void hideOverlayHint();
  void updateOverlayHint();

  CtxMenu* d_ctxMenu = nullptr;
  void showCtxMenu(const CtxMenuContent& i_ctxMenuContent);
  void hideCtxMenu();
};
