#pragma once

#include "ActionsController.h"
#include "Fwd.h"
#include "GameStates.h"
#include "GuiManager.h"
#include "ViewController.h"

#include <LaggyDx/App.h>


class Game : public Dx::App
{
public:
  Game();
  ~Game();

  const GameSettings& getGameSettings() const;

  Session* getSession() const;
  GuiManager& getGui();

  void newSession();
  void closeSession();
  void closeApplication();
  void saveSession();
  void loadSession();

private:
  GameState d_state = GameState::NotLoaded;
  void setState(GameState i_newState);
  void checkState();
  void onNotLoaded();
  void onLoading();
  void onGameLoaded();
  std::future<std::optional<std::string>> d_loadResourcesFuture;
  std::optional<std::string> loadResources();


  GuiManager d_guiManager;


  std::shared_ptr<Session> d_session;
  void attachSession(std::shared_ptr<Session> i_session);
  void detachSession();
  void startNewSession();


  std::unique_ptr<ViewController> d_viewController;
  void createViewController();


  ActionsController d_actionsController;


  virtual void onStart() override;
  virtual void update(double i_dt) override;
  virtual void render() override;
  virtual void onMouseMove(Sdk::Vector2I i_moveDiff) override;
  virtual bool onMouseClick(Dx::MouseKey i_key) override;
  virtual void onMouseRelease(Dx::MouseKey i_key) override;
};
