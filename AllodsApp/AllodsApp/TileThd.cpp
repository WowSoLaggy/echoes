#include "stdafx.h"
#include "TileThd.h"

#include "Constants.h"
#include "Entity.h"
#include "Materials.h"
#include "Tile.h"


TileThd::TileThd(Tile& i_tile)
  : d_tile(i_tile)
{
}


std::optional<double> TileThd::getTemperature() const
{
  return d_tile.getTemperature();
}

void TileThd::setTemperature(const double i_t)
{
  d_tile.setTemperature(i_t);
}

double TileThd::getThermalConductivity() const
{
  const int gasAmount = d_tile.getUnit().getGasAmount();
  if (gasAmount <= 0)
    return Constants::VacuumThermalConductivity;

  double conductivity = 0;
  for (const auto& [gas, amount] : d_tile.getUnit().getGases())
  {
    CONTRACT_ASSERT(amount > 0);
    const auto material = getGasMaterial(static_cast<Gas>(gas));
    const double partialConductivity = getMaterialThermalConductivity(material) * ((double)amount / gasAmount);
    conductivity += partialConductivity;
  }

  return conductivity;
}

double TileThd::getHeatCapacity() const
{
  const int gasAmount = d_tile.getUnit().getGasAmount();
  if (gasAmount <= 0)
    return Constants::VacuumHeatCapacity;

  double heatCapacity = 0;
  for (const auto& [gas, amount] : d_tile.getUnit().getGases())
  {
    CONTRACT_ASSERT(amount > 0);
    const auto material = getGasMaterial(static_cast<Gas>(gas));
    const double partialHeatCapacity = getMaterialHeatCapacity(material) * ((double)amount / gasAmount);
    heatCapacity += partialHeatCapacity;
  }

  const double heatCapacityMassMultiplier = gasAmount / Constants::PaInOneAtm;

  return heatCapacity * heatCapacityMassMultiplier;
}


bool TileThd::isAirTight() const
{
  return d_tile.isAirTight();
}


Dx::thd::Unit& TileThd::getUnit()
{
  return d_tile.getUnit();
}

const Dx::thd::Unit& TileThd::getUnit() const
{
  return d_tile.getUnit();
}


std::vector<Dx::thd::IThdObject*> TileThd::getHeatAgents() const
{
  std::vector<Dx::thd::IThdObject*> heatAgents;
  for (auto& entity : d_tile.getEntities())
    heatAgents.push_back(entity);
  return heatAgents;
}



void TileThd::afterUpdate(const double i_dt)
{
  if (d_tile.isSpaceExposed())
    leakGasesToSpace(i_dt);
}


void TileThd::leakGasesToSpace(double i_dt)
{
  const double initialGasAmount = getUnit().getGasAmount();
  if (initialGasAmount > 0)
  {
    const double newGasAmount = initialGasAmount * std::exp(-Constants::GasInSpaceDecayFactor * i_dt);
    const double decayGasShare = 1 - newGasAmount / initialGasAmount;
    const auto gasesToRemove = d_tile.getUnit().extractGases(decayGasShare);
    d_tile.getUnit().removeGases(gasesToRemove);
  }
}
