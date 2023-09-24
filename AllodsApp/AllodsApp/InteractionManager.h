#pragma once

#include "Fwd.h"

#include <LaggyDx/MouseKeys.h>


class InteractionManager
{
public:
  InteractionManager(Session& i_session);

  bool onMouseClick(Dx::MouseKey i_key);

private:
  Session& d_session;
};
