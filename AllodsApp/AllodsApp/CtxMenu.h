#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/Panel.h>


class CtxMenu : public Dx::Panel
{
public:
  void setContext(const CtxMenuContent& i_ctxMenuContent);

  void setText();
  void setActions();

private:
  Dx::Label* d_label = nullptr;
};
