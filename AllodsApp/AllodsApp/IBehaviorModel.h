#pragma once

#include "BehaviorModels.h"
#include "Fwd.h"


class IBehaviorModel
{
public:
  static BehaviorModelPtr get(BehaviorModel i_model, Structure& i_structure);

public:
  virtual ~IBehaviorModel() = default;

  virtual void interact() = 0;
};
