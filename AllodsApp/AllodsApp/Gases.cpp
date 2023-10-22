#include "stdafx.h"
#include "Gases.h"


namespace
{
  const std::unordered_map<Gas, std::string> GasMap {
    { Gas::Oxygen, "Oxygen" },
    { Gas::CarbonDioxide, "Carbon Dioxide" },
  };

} // anonym NS

DEFINE_ENUM_STR(Gas, GasMap);
