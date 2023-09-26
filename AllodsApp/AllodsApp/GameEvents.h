#pragma once

#include "GameStates.h"

#include <LaggySdk/IEvent.h>


class GameStateChangedEvent : public Sdk::IEvent
{
public:
  GameStateChangedEvent(const GameState i_newState)
    : d_newState(i_newState)
  {
  }

  GameState getNewState() const
  {
    return d_newState;
  }

private:
  const GameState d_newState;
};
