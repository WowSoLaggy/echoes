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
  , d_actionsController(*this)
{
}

Game::~Game()
{
  if (getSession())
    onExitSession();
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


void Game::onNewSession()
{
  d_guiManager.hideMainMenu();
  startNewSession();
  d_guiManager.createInGameMenu();
  d_actionsController.setInGameActions();
}

void Game::onExitSession()
{
  detachSession();
}

void Game::onCloseApplication()
{
  stop();
}
