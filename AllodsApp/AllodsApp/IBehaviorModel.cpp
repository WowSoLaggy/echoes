#include "stdafx.h"
#include "IBehaviorModel.h"

#include "ContainerBehavior.h"
#include "DoorBehavior.h"
#include "LampBehavior.h"


BehaviorModelPtr IBehaviorModel::get(BehaviorModel i_model, Entity& i_entity)
{
  switch (i_model)
  {
  case BehaviorModel::None:
    return nullptr;
  case BehaviorModel::Door:
    return std::make_shared<DoorBehavior>(i_entity);
  case BehaviorModel::Lamp:
    return std::make_shared<LampBehavior>(i_entity);
  case BehaviorModel::Container:
    return std::make_shared<ContainerBehavior>(i_entity);
  default:
    CONTRACT_THROW;
  }
}


void IBehaviorModel::interact()
{
}
