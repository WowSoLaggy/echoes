#include "stdafx.h"
#include "GasThd.h"

#include "Constants.h"
#include "Materials.h"

#include <LaggyDx/GasUnit.h>


void GasThd::setTemperature(double i_temperature)
{
  d_temperature = i_temperature;
}

double GasThd::getTemperature() const
{
  return d_temperature;
}

double GasThd::getThermalConductivity() const
{
  const int gasAmount = d_gasUnit.getGasAmount();
  if (gasAmount <= 0)
    return Constants::VacuumThermalConductivity;

  double conductivity = 0;
  for (const auto& [gas, amount] : d_gasUnit.getGases())
  {
    CONTRACT_ASSERT(amount > 0);
    const auto material = getGasMaterial(static_cast<Gas>(gas));
    const double partialConductivity = getMaterialThermalConductivity(material) * ((double)amount / gasAmount);
    conductivity += partialConductivity;
  }

  // `conductivityMassMultiplier` simulates that gas with higher pressure has higher thermal conductivity
  // while no pressure means no thermal conductivity
  const double conductivityMassMultiplier = gasAmount / Constants::PaInOneAtm;

  return conductivity * conductivityMassMultiplier;
}

double GasThd::getHeatCapacity() const
{
  const int gasAmount = d_gasUnit.getGasAmount();
  if (gasAmount <= 0)
    return Constants::VacuumHeatCapacity;

  double heatCapacity = 0;
  for (const auto& [gas, amount] : d_gasUnit.getGases())
  {
    CONTRACT_ASSERT(amount > 0);
    const auto material = getGasMaterial(static_cast<Gas>(gas));
    const double partialHeatCapacity = getMaterialHeatCapacity(material) * ((double)amount / gasAmount);
    heatCapacity += partialHeatCapacity;
  }

  // `heatCapacityMassMultiplier` simulates that gas with higher pressure has higher heat capacity
  const double heatCapacityMassMultiplier = gasAmount / Constants::PaInOneAtm;

  return heatCapacity * heatCapacityMassMultiplier;
}


Dx::thd::GasUnit* GasThd::getGasUnit()
{
  return &d_gasUnit;
}
const Dx::thd::GasUnit* GasThd::getGasUnit() const
{
  return &d_gasUnit;
}
