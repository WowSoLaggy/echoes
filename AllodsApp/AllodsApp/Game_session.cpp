#include "stdafx.h"
#include "Game.h"

#include "GameSettings.h"
#include "SessionEvents.h"
#include "SessionLoader.h"
#include "SessionSaver.h"

#include <LaggySdk/Files.h>


namespace
{
  fs::path getQuickSavePath(const fs::path& i_savesFolder)
  {
    return Sdk::getExeFolder() / i_savesFolder / "quick_save.sav";
  }

} // anonym NS


Session* Game::getSession() const
{
  return d_session.get();
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


void Game::attachSession(std::shared_ptr<Session> i_session)
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
  auto session = SessionLoader::createNew("Test Scenario");
  attachSession(std::move(session));
}

void Game::saveSession()
{
  CONTRACT_EXPECT(d_session);
  SessionSaver::save(*d_session, getQuickSavePath(getGameSettings().savesPath));
}

void Game::loadSession()
{
  auto session = SessionLoader::load(getQuickSavePath(getGameSettings().savesPath));
  attachSession(std::move(session));
}
