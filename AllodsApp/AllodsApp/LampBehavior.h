#pragma once

#include "Fwd.h"
#include "IBehaviorModel.h"


class LampBehavior : public IBehaviorModel
{
public:
  LampBehavior(Entity& i_lamp);

  virtual void interact() override;

  void turnOn();
  void turnOff();
  void switchState();

  bool isOn() const;
  bool isOff() const;

private:

  enum class LampState
  {
    On,
    Off,
  };

  Entity& d_lamp;
  LampState d_state = LampState::On;
};
