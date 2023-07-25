#include "stdafx.h"
#include "Game.h"

#include "SessionEvents.h"
#include "SessionLoader.h"

#include <LaggyDx/GameSettings.h>


namespace
{
  const Dx::GameSettings& getGameSettings()
  {
    static Dx::GameSettings settings;
    return settings;
  }

} // anonym NS


Game::Game()
  : Dx::Game(getGameSettings())
{
}


Session* Game::getSession() const { return d_session.get(); }


void Game::onGameStart()
{
  createViewController();
  startNewSession();
}

void Game::update(double i_dt)
{
  if (d_viewController)
    d_viewController->update(i_dt);
}

void Game::render()
{
  if (d_viewController)
    d_viewController->render();
}


void Game::attachSession(std::unique_ptr<Session> i_session)
{
  CONTRACT_EXPECT(d_session.get() != i_session.get());

  if (d_session)
    detachSession();

  d_session = std::move(i_session);

  if (d_session)
    notify(SessionAttachedEvent(*d_session));
}

void Game::detachSession()
{
  CONTRACT_EXPECT(d_session);

  notify(SessionDetachedEvent(*d_session));
  d_session.reset();
}

void Game::startNewSession()
{
  auto newSession = SessionLoader().createNew();
  attachSession(std::make_unique<Session>(std::move(newSession)));
}


void Game::createViewController()
{
  d_viewController = std::make_unique<ViewController>(*this);
}
