#include "stdafx.h"
#include "AtmoOverlay.h"

#include "Location.h"


AtmoOverlay::AtmoOverlay(const Location& i_location)
  : d_location(i_location)
{
}


OverlayType AtmoOverlay::getType() const
{
  return OverlayType::Atmo;
}

Dx::Color AtmoOverlay::getColor(const TileCoord& i_tileCoord) const
{
  return { 0.5f, 1.0f, 0.5f, 0.5f };
}
