#pragma once

#include "Fwd.h"
#include "IBehaviorModel.h"

#include <LaggySdk/EventHandler.h>


class DoorBehavior : public IBehaviorModel, public Sdk::EventHandler
{
public:
  enum class State : std::int32_t
  {
    Open = 0,
    Opening,
    Closing,
    Closed,
  };
  DECLARE_ENUM_STR(State);

public:
  DoorBehavior();
  DoorBehavior(Entity& i_door);

  virtual void processEvent(const Sdk::IEvent& i_event) override;
  virtual void pushFields() override;
  virtual void interact() override;

  virtual BehaviorModel getModelType() const override;
  virtual std::string getDescription() const override;

  void setDoor(Entity& i_door);

  void open();
  void close();

  bool isAirTight() const;

private:
  Entity* d_door = nullptr;
  State d_state = State::Closed;

  Entity& getDoor() const;

  void onAnimationStopped();
};
