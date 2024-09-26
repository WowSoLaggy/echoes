#include "stdafx.h"
#include "Materials.h"


namespace
{
  const std::unordered_map<Gas, Material> GasMaterialsMap{
    { Gas::Oxygen, Material::Oxygen },
    { Gas::CarbonDioxide, Material::CarbonDioxide },
  };

  const std::unordered_map<Material, std::string> MaterialsMap{
    { Material::Bio, "Bio" },

    { Material::Metal, "Metal" },
    { Material::InsulatedMetal, "InsulatedMetal" },
    { Material::Glass, "Glass" },

    { Material::Oxygen, "Oxygen" },
    { Material::CarbonDioxide, "CarbonDioxide" },
  };

  // W / (m * K)
  const std::unordered_map<Material, double> ThermalConductivityMap{
    { Material::Bio, 0.5 },

    { Material::Metal, 50.0 },
    { Material::InsulatedMetal, 0.01 },
    { Material::Glass, 1.0 },

    { Material::Oxygen, 0.25 },
    { Material::CarbonDioxide, 0.25 },
  };

  // J / (kg * K)
  const std::unordered_map<Material, double> HeatCapacityMap{
    { Material::Bio, 3500.0 },

    { Material::Metal, 500 },
    { Material::InsulatedMetal, 500.0 },
    { Material::Glass, 850.0 },

    { Material::Oxygen, 780.0 },
    { Material::CarbonDioxide, 780.0 },
  };

} // anonym NS

DEFINE_ENUM_STR(Material, MaterialsMap);


Material getGasMaterial(const Gas i_gas)
{
  return GasMaterialsMap.at(i_gas);
}


double getMaterialThermalConductivity(Material i_material)
{
  return ThermalConductivityMap.at(i_material);
}

double getMaterialHeatCapacity(Material i_material)
{
  return HeatCapacityMap.at(i_material);
}
