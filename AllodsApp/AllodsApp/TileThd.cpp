#include "stdafx.h"
#include "TileThd.h"

#include "Entity.h"
#include "Tile.h"


TileThd::TileThd(Tile& i_tile)
  : d_tile(i_tile)
{
}


std::vector<Dx::thd::IThdObject*> TileThd::getThdObjects() const
{
  std::vector<Dx::thd::IThdObject*> heatAgents;
  
  for (auto& entity : d_tile.getEntities())
    heatAgents.push_back(entity);

  if (!d_tile.isAirTight())
    heatAgents.push_back(&d_tile.getGasUnitThd());

  return heatAgents;
}


void TileThd::leakGasesToSpace(double i_dt)
{
  /*const double initialGasAmount = getUnit().getGasAmount();
  if (initialGasAmount > 0)
  {
    const double newGasAmount = initialGasAmount * std::exp(-Constants::GasInSpaceDecayFactor * i_dt);
    const double decayGasShare = 1 - newGasAmount / initialGasAmount;
    const auto gasesToRemove = d_tile.getUnit().extractGases(decayGasShare);
    d_tile.getUnit().removeGases(gasesToRemove);
  }*/
}
