#pragma once

#include "Fwd.h"
#include "IBehaviorModel.h"

#include <LaggySdk/EventHandler.h>


class DoorBehavior : public IBehaviorModel, public Sdk::EventHandler
{
public:
  DoorBehavior(Structure& i_structure);

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  virtual void interact() override;

  void open();
  void close();

private:
  
  enum class DoorState
  {
    Open,
    Opening,
    Closing,
    Closed,
  };

  Structure& d_structure;

  DoorState d_state = DoorState::Closed;

  void onAnimationStopped();
};
