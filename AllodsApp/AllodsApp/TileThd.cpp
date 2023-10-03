#include "stdafx.h"
#include "TileThd.h"

#include "Tile.h"


TileThd::TileThd(Tile& i_tile)
  : d_tile(i_tile)
{
}


double TileThd::getT() const
{
  return d_tile.getT();
}

void TileThd::setT(const double i_t)
{
  d_tile.setT(i_t);
}
