#pragma once

#include <LaggySdk/EnumStr.h>


enum class BehaviorModel : std::int32_t
{
  None = 0,

  Door,
  Lamp,
  Container,

  Count
};


DECLARE_ENUM_STR(BehaviorModel)
