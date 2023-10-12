#pragma once

#include "BehaviorModels.h"
#include "Fwd.h"


class IBehaviorModel
{
public:
  static BehaviorModelPtr get(BehaviorModel i_model, Entity& i_entity);

public:
  virtual ~IBehaviorModel() = default;

  virtual void interact();
};
