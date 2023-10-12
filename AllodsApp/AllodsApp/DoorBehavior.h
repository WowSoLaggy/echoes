#pragma once

#include "Fwd.h"
#include "IBehaviorModel.h"

#include <LaggySdk/EventHandler.h>


class DoorBehavior : public IBehaviorModel, public Sdk::EventHandler
{
public:
  DoorBehavior(Entity& i_door);

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  virtual void interact() override;

  void open();
  void close();

private:
  
  enum class State
  {
    Open,
    Opening,
    Closing,
    Closed,
  };

  Entity& d_door;
  State d_state = State::Closed;

  void onAnimationStopped();
};
