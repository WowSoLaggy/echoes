#include "stdafx.h"
#include "TileThd.h"

#include "Entity.h"
#include "Structure.h"
#include "Tile.h"


TileThd::TileThd(Tile& i_tile)
  : d_tile(i_tile)
{
}


std::vector<Dx::thd::IThdObject*> TileThd::getThdObjectsAll() const
{
  std::vector<Dx::thd::IThdObject*> agents;
  
  for (auto& entity : d_tile.getEntities())
    agents.push_back(entity);

  agents.push_back(&d_tile.getGasUnitThd());

  return agents;
}

std::vector<Dx::thd::IThdObject*> TileThd::getThdObjectsExternal() const
{
  std::vector<Dx::thd::IThdObject*> agents;

  for (auto& entity : d_tile.getStructures())
    agents.push_back(entity);

  agents.push_back(&d_tile.getGasUnitThd());

  return agents;
}
