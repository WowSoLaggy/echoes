#pragma once

#include "Gases.h"

#include <LaggySdk/EnumStr.h>


enum class Material : std::int32_t
{
  Bio,

  Metal,
  InsulatedMetal,
  Glass,

  Oxygen,
  CarbonDioxide,

  Default = Metal,
};

DECLARE_ENUM_STR(Material);


Material getGasMaterial(const Gas i_gasId);

double getMaterialThermalConductivity(Material i_material);
double getMaterialHeatCapacity(Material i_material);
