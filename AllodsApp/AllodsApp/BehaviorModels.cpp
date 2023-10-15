#include "stdafx.h"
#include "BehaviorModels.h"


namespace
{
  const std::unordered_map<BehaviorModel, std::string> BehaviorModelStrings {
    { BehaviorModel::None, "None" },
    { BehaviorModel::Door, "Door" },
    { BehaviorModel::Lamp, "Lamp" },
    { BehaviorModel::Container, "Container" },
  };

} // anonym NS


DEFINE_ENUM_STR(BehaviorModel, BehaviorModelStrings)
