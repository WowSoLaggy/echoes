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

  heatAgents.push_back(&d_tile.getGasUnitThd());

  return heatAgents;
}
