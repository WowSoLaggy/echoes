#include "stdafx.h"
#include "TempOverlay.h"


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
  return { 1.0f, 0.5f, 0.5f, 0.5f };
}
