#include "stdafx.h"
#include "Game.h"

#include "GameSettings.h"
#include "Session.h"


namespace
{
  std::unique_ptr<Dx::AppSettings> getAppSettings()
  {
    auto settings = std::make_unique<GameSettings>();

    /*settings.screenWidth = 1024;
    settings.screenHeight = 768;*/

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


const GameSettings& Game::getGameSettings() const
{
  return dynamic_cast<const GameSettings&>(App::getSettings());
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

  d_guiManager.update();

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
