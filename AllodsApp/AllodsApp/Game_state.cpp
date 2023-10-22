#include "stdafx.h"
#include "Game.h"

#include "GameEvents.h"
#include "GasPrototypesCollection.h"
#include "PrototypesCollection.h"

#include <LaggySdk/Files.h>


void Game::setState(const GameState i_newState)
{
  d_state = i_newState;
  notify(GameStateChangedEvent(d_state));
}


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

  setState(GameState::Loading);
}

void Game::onLoading()
{
  CONTRACT_EXPECT(d_state == GameState::Loading);

  CONTRACT_ASSERT(d_loadResourcesFuture.valid());
  if (d_loadResourcesFuture.wait_for(0ms) == std::future_status::timeout)
    return;

  const std::optional<std::string> errorMsgOpt = d_loadResourcesFuture.get();
  CONTRACT_ENSURE(!errorMsgOpt.has_value());

  onGameLoaded();
}

void Game::onGameLoaded()
{
  setState(GameState::Loaded);
  getInputDevice().showCursor();
}


std::optional<std::string> Game::loadResources()
{
  try
  {
    getResourceController().loadResources();

    const fs::path configsPath = Sdk::getExeFolder() / getSettings().dataFolder / "Configs";
    PrototypesCollection::load(configsPath);

    GasPrototypesCollection::initialize();
  }
  catch (const Sdk::DxException& i_exc)
  {
    return i_exc.what();
  }
  catch (...)
  {
    return "Unknown error occured";
  }

  return std::nullopt;
}
