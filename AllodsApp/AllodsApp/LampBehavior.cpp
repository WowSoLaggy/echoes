#include "stdafx.h"
#include "LampBehavior.h"

#include "AnimationUtils.h"


LampBehavior::LampBehavior()
{
}

LampBehavior::LampBehavior(Entity& i_lamp)
{
  setLamp(i_lamp);
}


void LampBehavior::pushFields()
{
  IBehaviorModel::pushFields();

  pushField("state", *((std::int32_t*)&d_state));
}


void LampBehavior::interact()
{
  switchState();
}


BehaviorModel LampBehavior::getModelType() const
{
  return BehaviorModel::Lamp;
}


Entity& LampBehavior::getLamp() const
{
  return SAFE_DEREF(d_lamp);
}

void LampBehavior::setLamp(Entity& i_lamp)
{
  d_lamp = &i_lamp;
}


void LampBehavior::turnOn()
{
  if (isOn())
    return;

  d_state = State::On;
  AnimationUtils::playAnimation(getLamp(), "On", 1);
}

void LampBehavior::turnOff()
{
  if (isOff())
    return;

  d_state = State::Off;
  AnimationUtils::playAnimation(getLamp(), "Off", 1);
}

void LampBehavior::switchState()
{
  if (isOn())
    turnOff();
  else
    turnOn();
}


bool LampBehavior::isOn() const
{
  return d_state == State::On;
}

bool LampBehavior::isOff() const
{
  return d_state == State::Off;
}
