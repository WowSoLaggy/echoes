#pragma once

#include "Session.h"
#include "ViewController.h"

#include <LaggyDx/App.h>


class Game : public Dx::App
{
public:
  Game();

  Session* getSession() const;

private:
  std::unique_ptr<Session> d_session;
  std::unique_ptr<ViewController> d_viewController;

  void attachSession(std::unique_ptr<Session> i_session);
  void detachSession();
  void startNewSession();

  void createViewController();

  virtual void onStart() override;
  virtual void update(double i_dt) override;
  virtual void render() override;
};
