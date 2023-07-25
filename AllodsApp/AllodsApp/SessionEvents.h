#pragma once

#include "Fwd.h"

#include <LaggySdk/IEvent.h>


class SessionEvent : public Sdk::IEvent
{
public:
  explicit SessionEvent(Session& i_session)
    : d_session(i_session)
  {
  }

  Session& getSession() const
  {
    return d_session;
  }

private:
  Session& d_session;
};


class SessionAttachedEvent : public SessionEvent
{
public:
  using SessionEvent::SessionEvent;
};

class SessionDetachedEvent : public SessionEvent
{
public:
  using SessionEvent::SessionEvent;
};
