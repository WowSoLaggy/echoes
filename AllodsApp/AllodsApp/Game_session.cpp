#include "stdafx.h"
#include "Game.h"

#include "SessionEvents.h"
#include "SessionLoader.h"


Session* Game::getSession() const { return d_session.get(); }


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
  auto session = SessionLoader().createNew();
  attachSession(std::move(session));
}
