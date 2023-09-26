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
    closeSession();
}


GuiManager& Game::getGui() { return d_guiManager; }


void Game::onStart()
{
  setState(GameState::NotLoaded);
}

void Game::update(double i_dt)
{
  checkState();

  if (d_session)
    d_session->update(i_dt);

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

void Game::onMouseRelease(Dx::MouseKey i_key)
{
  if (d_session)
    d_session->onMouseRelease(i_key);

  App::onMouseRelease(i_key);
}


void Game::createViewController()
{
  d_viewController = std::make_unique<ViewController>(*this);
}


void Game::newSession()
{
  startNewSession();
}

void Game::closeSession()
{
  detachSession();
}

void Game::closeApplication()
{
  stop();
}
