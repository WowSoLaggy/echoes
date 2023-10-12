#include "stdafx.h"
#include "ContainerBehavior.h"

#include "AnimationUtils.h"


ContainerBehavior::ContainerBehavior(Entity& i_container)
  : d_container(i_container)
{
}


void ContainerBehavior::interact()
{
  switchState();
}


void ContainerBehavior::open()
{
  if (isOpen())
    return;

  d_state = State::Open;
  AnimationUtils::playAnimation(d_container, "Open", 1);
}

void ContainerBehavior::close()
{
  if (isClosed())
    return;

  d_state = State::Closed;
  AnimationUtils::playAnimation(d_container, "Close", 1);
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
