#include "stdafx.h"
#include "IBehaviorModel.h"

#include "DoorBehavior.h"


BehaviorModelPtr IBehaviorModel::get(BehaviorModel i_model, Entity& i_entity)
{
  if (i_model == BehaviorModel::Door)
    return std::make_shared<DoorBehavior>(i_entity);

  return nullptr;
}
