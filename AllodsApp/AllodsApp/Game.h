#pragma once

#include "GameStates.h"
#include "Session.h"
#include "ViewController.h"

#include <LaggyDx/App.h>


class Game : public Dx::App
{
public:
  Game();

  Session* getSession() const;

private:
  GameState d_state = GameState::NotLoaded;
  void checkState();
  void onNotLoaded();
  void onLoading();
  void onGameLoaded();
  std::future<bool> d_loadResourcesFuture;
  bool loadResources();


  std::unique_ptr<Session> d_session;
  void attachSession(std::unique_ptr<Session> i_session);
  void detachSession();
  void startNewSession();


  std::unique_ptr<ViewController> d_viewController;
  void createViewController();


  virtual void onStart() override;
  virtual void update(double i_dt) override;
  virtual void render() override;
};
