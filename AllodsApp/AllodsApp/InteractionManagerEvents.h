#pragma once

#include "Fwd.h"

#include <LaggySdk/IEvent.h>


class ShowCtxMenuEvent : public Sdk::IEvent
{
public:
  ShowCtxMenuEvent(const CtxMenuContent& i_ctxMenuContent)
    : d_ctxMenuContent(i_ctxMenuContent)
  {
  }

  const CtxMenuContent& getCtxMenuContent() const
  {
    return d_ctxMenuContent;
  }

private:
  const CtxMenuContent& d_ctxMenuContent;
};

class HideCtxMenuEvent : public Sdk::IEvent
{
};
