#pragma once

#include <LaggySdk/EnumStr.h>


enum class Gas : std::int32_t
{
  Oxygen = 0,
  CarbonDioxide,
};

DECLARE_ENUM_STR(Gas);
