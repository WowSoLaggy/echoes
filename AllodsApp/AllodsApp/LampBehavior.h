#pragma once

#include "Fwd.h"
#include "IBehaviorModel.h"

#include <LaggySdk/EnumStr.h>


class LampBehavior : public IBehaviorModel
{
public:
  enum class State : std::int32_t
  {
    On = 0,
    Off,
  };
  DECLARE_ENUM_STR(State);

public:
  LampBehavior();
  LampBehavior(Entity& i_lamp);

  virtual void pushFields() override;
  virtual void interact() override;

  virtual BehaviorModel getModelType() const override;
  virtual std::string getDescription() const override;

  void setLamp(Entity& i_lamp);

  void turnOn();
  void turnOff();
  void switchState();

  bool isOn() const;
  bool isOff() const;

private:
  Entity* d_lamp = nullptr;
  State d_state = State::On;

  Entity& getLamp() const;
};
