#pragma once

#include "Fwd.h"

#include <LaggySdk/IEvent.h>


class LocationEvent : public Sdk::IEvent
{
public:
  explicit LocationEvent(Location& i_location)
    : d_location(i_location)
  {
  }

  Location& getLocation() const
  {
    return d_location;
  }

private:
  Location& d_location;
};


class LocationAddedEvent : public LocationEvent
{
public:
  using LocationEvent::LocationEvent;
};

class LocationRemovedEvent : public LocationEvent
{
public:
  using LocationEvent::LocationEvent;
};
