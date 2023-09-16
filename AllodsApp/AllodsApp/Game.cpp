#include "stdafx.h"
#include "Game.h"

#include <LaggyDx/AppSettings.h>


namespace
{
  const Dx::AppSettings& getAppSettings()
  {
    static Dx::AppSettings settings;
    return settings;
  }

} // anonym NS


Game::Game()
  : Dx::App(getAppSettings())
  , d_guiManager(*this)
{
}


void Game::onStart()
{
  d_state = GameState::NotLoaded;
}

void Game::update(double i_dt)
{
  checkState();

  if (d_viewController)
    d_viewController->update(i_dt);
}

void Game::render()
{
  if (d_viewController)
    d_viewController->render();
}


void Game::createViewController()
{
  d_viewController = std::make_unique<ViewController>(*this);
}


void Game::onNewGame()
{
  d_guiManager.hideMainMenu();
  startNewSession();
}

void Game::onExit()
{
  stop();
}
