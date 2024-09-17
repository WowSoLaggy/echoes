#include "stdafx.h"
#include "DoorBehavior.h"

#include "AnimationUtils.h"
#include "Entity.h"

#include <LaggyDx/AnimationEvents.h>


namespace
{
  const std::unordered_map<DoorBehavior::State, std::string> DoorBehaviorStatesStrings {
    { DoorBehavior::State::Open, "Open" },
    { DoorBehavior::State::Opening, "Opening" },
    { DoorBehavior::State::Closing, "Closing" },
    { DoorBehavior::State::Closed, "Closed" },
  };

} // anonym NS

DEFINE_ENUM_STR(DoorBehavior::State, DoorBehaviorStatesStrings)


DoorBehavior::DoorBehavior()
{
}

DoorBehavior::DoorBehavior(Entity& i_door)
{
  setDoor(i_door);
}


void DoorBehavior::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const Dx::AnimationStoppedEvent*>(&i_event))
    onAnimationStopped();
  else if (const auto* event = dynamic_cast<const Dx::AnimationFrameChangedEvent*>(&i_event))
    onAnimationUpdated(event->getCurrentFrame(), event->getAnimationLength());
}


void DoorBehavior::pushFields()
{
  IBehaviorModel::pushFields();

  pushField("state", *((std::int32_t*)&d_state));
}


void DoorBehavior::interact()
{
  if (d_state == State::Closed)
    open();
  else if (d_state == State::Open)
    close();
}


BehaviorModel DoorBehavior::getModelType() const
{
  return BehaviorModel::Door;
}

std::string DoorBehavior::getDescription() const
{
  return "State: " + StateStr::toString(d_state);
}


Entity& DoorBehavior::getDoor() const
{
  return SAFE_DEREF(d_door);
}

void DoorBehavior::setDoor(Entity& i_door)
{
  if (d_door)
    disconnectFrom(d_door->getAnimationPlayer());

  d_door = &i_door;

  if (d_door)
    connectTo(d_door->getAnimationPlayer());
}


void DoorBehavior::open()
{
  AnimationUtils::playAnimation(getDoor(), "Open", 1);
  d_state = State::Opening;
}

void DoorBehavior::close()
{
  AnimationUtils::playAnimation(getDoor(), "Close", 1);
  d_state = State::Closing;
}


void DoorBehavior::onAnimationStopped()
{
  if (d_state == State::Opening)
  {
    d_state = State::Open;
    updateOccupiedVolume(0);
  }
  else if (d_state == State::Closing)
  {
    d_state = State::Closed;
    updateOccupiedVolume(1);
  }
}

void DoorBehavior::onAnimationUpdated(const int i_curFrame, const int i_totalFrames)
{
  // Update occupied volume
  if (d_state == State::Opening)
    updateOccupiedVolume(1.0 - i_curFrame / static_cast<double>(i_totalFrames));
  else if (d_state == State::Closing)
    updateOccupiedVolume(i_curFrame / static_cast<double>(i_totalFrames));
}


void DoorBehavior::updateOccupiedVolume(const double i_occupiedVolume)
{
  getDoor().setVolume(i_occupiedVolume);
}
