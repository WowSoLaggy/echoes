#include "stdafx.h"
#include "ContainerBehavior.h"

#include "AnimationUtils.h"


namespace
{
  const std::unordered_map<ContainerBehavior::State, std::string> ContainerBehaviorStatesStrings {
    { ContainerBehavior::State::Open, "Open" },
    { ContainerBehavior::State::Closed, "Closed" },
  };

} // anonym NS

DEFINE_ENUM_STR(ContainerBehavior::State, ContainerBehaviorStatesStrings)


ContainerBehavior::ContainerBehavior()
{
}

ContainerBehavior::ContainerBehavior(Entity& i_container)
{
  setContainer(i_container);
}


void ContainerBehavior::pushFields()
{
  IBehaviorModel::pushFields();

  pushField("state", *((std::int32_t*)&d_state));
}


void ContainerBehavior::interact()
{
  switchState();
}


BehaviorModel ContainerBehavior::getModelType() const
{
  return BehaviorModel::Container;
}

std::string ContainerBehavior::getDescription() const
{
  return "State: " + StateStr::toString(d_state);
}


Entity& ContainerBehavior::getContainer() const
{
  return SAFE_DEREF(d_container);
}

void ContainerBehavior::setContainer(Entity& i_container)
{
  d_container = &i_container;
}


void ContainerBehavior::open()
{
  if (isOpen())
    return;

  d_state = State::Open;
  AnimationUtils::playAnimation(getContainer(), "Open", 1);
}

void ContainerBehavior::close()
{
  if (isClosed())
    return;

  d_state = State::Closed;
  AnimationUtils::playAnimation(getContainer(), "Close", 1);
}

void ContainerBehavior::switchState()
{
  if (isOpen())
    close();
  else
    open();
}


bool ContainerBehavior::isOpen()
{
  return d_state == State::Open;
}

bool ContainerBehavior::isClosed()
{
  return d_state == State::Closed;
}
