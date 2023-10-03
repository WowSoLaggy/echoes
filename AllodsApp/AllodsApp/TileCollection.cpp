#include "stdafx.h"
#include "TileCollection.h"

#include "DummyTileThd.h"
#include "Location.h"
#include "TileThd.h"


TileCollection::TileCollection(Location& i_location)
  : d_location(i_location)
{
}


int TileCollection::minX() const
{
  return d_location.getMinX();
}

int TileCollection::minY() const
{
  return d_location.getMinY();
}

int TileCollection::maxX() const
{
  return d_location.getMaxX();
}

int TileCollection::maxY() const
{
  return d_location.getMaxY();
}


std::shared_ptr<Dx::thd::ITile> TileCollection::getTile(const Sdk::Vector2I& i_coords) const
{
  if (auto* tile = d_location.getTile(i_coords))
    return std::make_shared<TileThd>(*tile);

  return std::make_shared<DummyTileThd>();
}
