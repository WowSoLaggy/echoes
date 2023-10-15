#pragma once

#include <LaggySdk/EnumStr.h>


enum class BehaviorModel
{
  None = 0,

  Door,
  Lamp,
  Container,

  Count
};


DECLARE_ENUM_STR(BehaviorModel)
