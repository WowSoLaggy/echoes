#include "stdafx.h"
#include "IBehaviorModel.h"

#include "DoorBehavior.h"


BehaviorModelPtr IBehaviorModel::get(BehaviorModel i_model, Structure& i_structure)
{
  if (i_model == BehaviorModel::Door)
    return std::make_shared<DoorBehavior>(i_structure);

  return nullptr;
}
