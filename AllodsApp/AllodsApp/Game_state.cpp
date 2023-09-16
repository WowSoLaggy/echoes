#include "stdafx.h"
#include "Game.h"

#include "PrototypesCollection.h"

#include <LaggySdk/Files.h>


void Game::checkState()
{
  switch (d_state)
  {
  case GameState::NotLoaded:
    onNotLoaded();
    break;
  case GameState::Loading:
    onLoading();
    break;
  case GameState::Loaded:
    break;
  default:
    CONTRACT_ASSERT(false);
    break;
  }
}


void Game::onNotLoaded()
{
  CONTRACT_EXPECT(d_state == GameState::NotLoaded);

  createViewController();
  d_loadResourcesFuture = std::async(&Game::loadResources, this);

  d_guiManager.showLoadingScreen();

  d_state = GameState::Loading;
}

void Game::onLoading()
{
  CONTRACT_EXPECT(d_state == GameState::Loading);

  CONTRACT_ASSERT(d_loadResourcesFuture.valid());
  if (d_loadResourcesFuture.wait_for(0ms) == std::future_status::timeout)
    return;

  const bool success = d_loadResourcesFuture.get();
  CONTRACT_ENSURE(success);

  onGameLoaded();
}

void Game::onGameLoaded()
{
  d_state = GameState::Loaded;
  d_guiManager.hideLoadingScreen();
  d_guiManager.createMainMenu();

  getInputDevice().showCursor();
}


bool Game::loadResources()
{
  try
  {
    getResourceController().loadResources();

    const fs::path configsPath = Sdk::getExeFolder() / getSettings().dataFolder / "Configs";
    PrototypesCollection::load(configsPath);
  }
  catch (...)
  {
    return false;
  }

  return true;
}
