#include "stdafx.h"
#include "LampBehavior.h"

#include "AnimationUtils.h"

LampBehavior::LampBehavior(Entity& i_lamp)
  : d_lamp(i_lamp)
{
}


void LampBehavior::interact()
{
  switchState();
}


void LampBehavior::turnOn()
{
  if (isOn())
    return;

  d_state = LampState::On;
  AnimationUtils::playAnimation(d_lamp, "On", 1);
}

void LampBehavior::turnOff()
{
  if (isOff())
    return;

  d_state = LampState::Off;
  AnimationUtils::playAnimation(d_lamp, "Off", 1);
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
  return d_state == LampState::On;
}

bool LampBehavior::isOff() const
{
  return d_state == LampState::Off;
}
