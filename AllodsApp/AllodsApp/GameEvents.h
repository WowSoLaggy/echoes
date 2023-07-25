#pragma once

#include "Fwd.h"

#include <LaggySdk/IEvent.h>


class GameEvent : public Sdk::IEvent
{
public:
  explicit GameEvent(Game& i_game)
    : d_game(i_game)
  {
  }

  Game& getGame() const
  {
    return d_game;
  }

private:
  Game& d_game;
};
