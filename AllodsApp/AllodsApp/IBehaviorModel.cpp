#include "stdafx.h"
#include "IBehaviorModel.h"

#include "ContainerBehavior.h"
#include "DoorBehavior.h"
#include "GasTankBehavior.h"
#include "LampBehavior.h"

#include <LaggySdk/JsonSerializer.h>


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
  case BehaviorModel::GasTank:
    return std::make_shared<GasTankBehavior>(i_entity);
  default:
    CONTRACT_THROW();
  }
}

BehaviorModelPtr IBehaviorModel::deserialize(const Json::Value& i_json, Entity& i_entity)
{
  const auto modelType = static_cast<BehaviorModel>(i_json["modelType"].asInt());

  switch (modelType)
  {
  case BehaviorModel::None:
    return nullptr;
  case BehaviorModel::Door:
  {
    auto model = std::make_shared<DoorBehavior>(i_entity);
    Sdk::JsonSerializer::deserialize(*model, i_json);
    return model;
  }
  case BehaviorModel::Lamp:
  {
    auto model = std::make_shared<LampBehavior>(i_entity);
    Sdk::JsonSerializer::deserialize(*model, i_json);
    return model;
  }
  case BehaviorModel::Container:
  {
    auto model = std::make_shared<ContainerBehavior>(i_entity);
    Sdk::JsonSerializer::deserialize(*model, i_json);
    return model;
  }
  case BehaviorModel::GasTank:
  {
    auto model = std::make_shared<GasTankBehavior>(i_entity);
    Sdk::JsonSerializer::deserialize(*model, i_json);
    return model;
  }
  default:
    CONTRACT_THROW();
  }
}


void IBehaviorModel::pushFields()
{
  d_modelTypeCache = static_cast<int>(getModelType());
  pushField("modelType", d_modelTypeCache);
}

void IBehaviorModel::interact()
{
}


BehaviorActions IBehaviorModel::getActions(bool i_devMode) const
{
  return {};
}
