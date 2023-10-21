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


class DevModeSwitchEvent : public Sdk::IEvent
{
public:
  DevModeSwitchEvent(const bool i_enabled)
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


class PauseEvent : public Sdk::IEvent
{
};

class UnpauseEvent : public Sdk::IEvent
{
};


class ExitBuildRemovalEvent : public Sdk::IEvent
{
};


class OverlaySetEvent : public Sdk::IEvent
{
public:
  OverlaySetEvent(const IOverlay* i_overlay)
    : d_overlay(i_overlay)
  {
  }

  const IOverlay* getOverlay() const { return d_overlay; }

private:
  const IOverlay* d_overlay = nullptr;
};
