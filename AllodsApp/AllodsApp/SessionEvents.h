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


class GodModeEvent : public Sdk::IEvent
{
public:
  GodModeEvent(const bool i_enabled)
    : d_enabled(i_enabled)
  {
  }

  bool getEnabled() const
  {
    return d_enabled;
  }

private:
  bool d_enabled = false;
};


class BuildDraftSetEvent : public Sdk::IEvent
{
public:
  BuildDraftSetEvent(std::shared_ptr<BuildDraftInfo> i_info)
    : d_info(i_info)
  {
  }

  std::shared_ptr<BuildDraftInfo> getInfo() const
  {
    return d_info;
  }

private:
  std::shared_ptr<BuildDraftInfo> d_info;
};
