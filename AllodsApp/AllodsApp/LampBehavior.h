#pragma once

#include "Fwd.h"
#include "IBehaviorModel.h"


class LampBehavior : public IBehaviorModel
{
public:
  LampBehavior();
  LampBehavior(Entity* i_lamp);

  virtual void pushFields() override;
  virtual void interact() override;

  virtual BehaviorModel getModelType() const override;

  void setLamp(Entity* i_lamp);

  void turnOn();
  void turnOff();
  void switchState();

  bool isOn() const;
  bool isOff() const;

private:

  enum class State
  {
    On,
    Off,
  };

  Entity* d_lamp = nullptr;
  State d_state = State::On;

  Entity& getLamp() const;
};
