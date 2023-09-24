#include "stdafx.h"
#include "DoorBehavior.h"

#include "AnimationUtils.h"
#include "Structure.h"

#include <LaggyDx/AnimationEvents.h>


DoorBehavior::DoorBehavior(Structure& i_structure)
  : d_structure(i_structure)
{
  connectTo(d_structure.getAnimationPlayer());
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
  AnimationUtils::playAnimation(d_structure, "Open", 1);
  d_state = DoorState::Opening;
}

void DoorBehavior::close()
{
  AnimationUtils::playAnimation(d_structure, "Close", 1);
  d_state = DoorState::Closing;
}


void DoorBehavior::onAnimationStopped()
{
  if (d_state == DoorState::Opening)
    d_state = DoorState::Open;
  else if (d_state == DoorState::Closing)
    d_state = DoorState::Closed;
}
