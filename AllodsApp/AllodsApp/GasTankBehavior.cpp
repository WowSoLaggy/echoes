#include "stdafx.h"
#include "GasTankBehavior.h"

#include "Entity.h"
#include "Prototypes.h"


namespace
{
  const std::unordered_map<GasTankBehavior::State, std::string> GasTankBehaviorStatesStrings {
    { GasTankBehavior::State::Open, "Open" },
    { GasTankBehavior::State::Close, "Close" },
  };

} // anonym NS

DEFINE_ENUM_STR(GasTankBehavior::State, GasTankBehaviorStatesStrings)


GasTankBehavior::GasTankBehavior()
{
}

GasTankBehavior::GasTankBehavior(Entity& i_gasTank)
{
  setGasTank(i_gasTank);
}


void GasTankBehavior::pushFields()
{
  IBehaviorModel::pushFields();

  pushField("state", *((std::int32_t*)&d_state));
  pushObject("volumeUnit", d_volumeUnit);
}


void GasTankBehavior::interact()
{
  switchState();
}


BehaviorModel GasTankBehavior::getModelType() const
{
  return BehaviorModel::GasTank;
}

std::string GasTankBehavior::getDescription() const
{
  return "State: " + StateStr::toString(d_state);
}


Entity& GasTankBehavior::getGasTank() const
{
  return SAFE_DEREF(d_gasTank);
}

void GasTankBehavior::setGasTank(Entity& i_gasTank)
{
  d_gasTank = &i_gasTank;

  if (d_gasTank->hasPrototype())
    d_volumeUnit.setVolume(d_gasTank->getPrototype().volume);
}


void GasTankBehavior::open()
{
  if (isOpen())
    return;

  d_state = State::Open;
}

void GasTankBehavior::close()
{
  if (isClose())
    return;

  d_state = State::Close;
}

void GasTankBehavior::switchState()
{
  if (isOpen())
    close();
  else
    open();
}


bool GasTankBehavior::isOpen() const
{
  return d_state == State::Open;
}

bool GasTankBehavior::isClose() const
{
  return d_state == State::Close;
}
