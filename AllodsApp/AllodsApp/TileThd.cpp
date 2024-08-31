#include "stdafx.h"
#include "TileThd.h"

#include "Constants.h"
#include "Tile.h"


TileThd::TileThd(Tile& i_tile)
  : d_tile(i_tile)
{
}


std::optional<double> TileThd::getT() const
{
  return d_tile.getT();
}

void TileThd::setT(const double i_t)
{
  d_tile.setT(i_t);
}


double TileThd::getInsulationFactor() const
{
  return d_tile.getInsulationFactor();
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


void TileThd::afterUpdate(const double i_dt)
{
  if (d_tile.isSpaceExposed())
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
}
