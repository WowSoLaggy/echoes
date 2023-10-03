#include "stdafx.h"
#include "TempOverlay.h"

#include "Location.h"


TempOverlay::TempOverlay(const Location& i_location)
  : d_location(i_location)
{
}


OverlayType TempOverlay::getType() const
{
  return OverlayType::Temp;
}

Dx::Color TempOverlay::getColor(const TileCoord& i_tileCoord) const
{
  const auto* tile = d_location.getTile(i_tileCoord);
  if (!tile)
    return { 0, 0, 0, 0 };

  const double t = tile->getT();
  return { 1, 0, 0, (float)t / 100 };
}
