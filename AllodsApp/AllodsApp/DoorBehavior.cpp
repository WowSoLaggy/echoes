#include "stdafx.h"
#include "DoorBehavior.h"

#include "AnimationUtils.h"
#include "Entity.h"

#include <LaggyDx/AnimationEvents.h>


DoorBehavior::DoorBehavior(Entity& i_door)
  : d_door(i_door)
{
  connectTo(d_door.getAnimationPlayer());
}


void DoorBehavior::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const Dx::AnimationStoppedEvent*>(&i_event))
    onAnimationStopped();
}


void DoorBehavior::interact()
{
  if (d_state == DoorState::Closed)
    open();
  else if (d_state == DoorState::Open)
    close();
}


void DoorBehavior::open()
{
  AnimationUtils::playAnimation(d_door, "Open", 1);
  d_state = DoorState::Opening;
}

void DoorBehavior::close()
{
  AnimationUtils::playAnimation(d_door, "Close", 1);
  d_state = DoorState::Closing;
}


void DoorBehavior::onAnimationStopped()
{
  if (d_state == DoorState::Opening)
    d_state = DoorState::Open;
  else if (d_state == DoorState::Closing)
    d_state = DoorState::Closed;
}
