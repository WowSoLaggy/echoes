#include "stdafx.h"
#include "Gases.h"


namespace
{
  const std::unordered_map<Gas, std::string> GasMap {
    { Gas::Oxygen, "O2" },
    { Gas::CarbonDioxide, "CO2" },
  };

} // anonym NS

DEFINE_ENUM_STR(Gas, GasMap);
