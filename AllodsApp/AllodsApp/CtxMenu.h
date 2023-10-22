#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/Panel.h>


class CtxMenu : public Dx::Panel
{
public:
  CtxMenu(InteractionManager& i_interactionManager);

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  void setContext(const CtxMenuContent& i_ctxMenuContent);

private:
  InteractionManager& d_interactionManager;
  Dx::Label* d_label = nullptr;

  void onChildPressed();
};
