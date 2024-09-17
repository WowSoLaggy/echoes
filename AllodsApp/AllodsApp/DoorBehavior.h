#pragma once

#include "Fwd.h"
#include "IBehaviorModel.h"


class DoorBehavior : public IBehaviorModel
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

private:
  Entity* d_door = nullptr;
  State d_state = State::Closed;

  Entity& getDoor() const;

  void onAnimationStopped();
  void onAnimationUpdated(int i_curFrame, int i_totalFrames);
  // 0 - whole tile volume is occupied by the door, meaning that the door is fully closed and there is no space for gas
  // 1 - the door is fully open, meaning that the whole tile volume is available for gas
  void updateOccupiedVolume(double i_occupiedVolume);
};
