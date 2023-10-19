#pragma once

#include "Fwd.h"

#include <LaggyDx/MouseKeys.h>

#include <LaggySdk/EventHandler.h>


class InteractionManager : public Sdk::EventHandler
{
public:
  InteractionManager(Session& i_session);

  bool onMouseClick(Dx::MouseKey i_key);

  bool showContextMenu();
  bool hideContextMenu();

private:
  Session& d_session;

  bool d_isContextMenuShown = false;

  bool tryInteract();
};
