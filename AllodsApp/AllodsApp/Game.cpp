#include "stdafx.h"
#include "Game.h"

#include <LaggyDx/AppSettings.h>


namespace
{
  const Dx::AppSettings& getAppSettings()
  {
    static Dx::AppSettings settings;
    settings.screenWidth = 1024;
    settings.screenHeight = 768;
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


GuiManager& Game::getGui() { return d_guiManager; }


void Game::onStart()
{
  d_state = GameState::NotLoaded;
}

void Game::update(double i_dt)
{
  checkState();

  if (d_session)
    d_session->update();

  if (d_viewController)
    d_viewController->update(i_dt);
}

void Game::render()
{
  if (d_viewController)
    d_viewController->render();
}

void Game::onMouseMove(Sdk::Vector2I i_moveDiff)
{
  if (d_session)
    d_session->onMouseMove();

  App::onMouseMove(std::move(i_moveDiff));
}

bool Game::onMouseClick(Dx::MouseKey i_key)
{
  if (App::onMouseClick(i_key))
    return true;

  if (d_session)
  {
    if (d_session->onMouseClick(i_key))
      return true;
  }
  
  return false;
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
}

void Game::onExitSession()
{
  detachSession();
}

void Game::onCloseApplication()
{
  stop();
}
