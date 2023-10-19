#pragma once

#include <LaggySdk/IEvent.h>


class ShowContextMenuEvent : public Sdk::IEvent
{
public:
  ShowContextMenuEvent()
  {
  }
};

class HideContextMenuEvent : public Sdk::IEvent
{
public:
  HideContextMenuEvent() = default;
};
