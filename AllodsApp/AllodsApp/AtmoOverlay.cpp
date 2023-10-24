#include "stdafx.h"
#include "AtmoOverlay.h"

#include "Location.h"
#include "Units.h"

#include <LaggySdk/Math.h>
#include <LaggySdk/StringUtils.h>


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
  const auto tile = d_location.getTile(i_tileCoord);
  if (!tile)
    return { 0, 0, 0, 0 };

  const double pressurePa = tile->getVolumeUnit().getPressure();
  const double pressureAtm = Units::paToAtm(pressurePa);
  const double pressureNorm = Sdk::clamp<double>(pressureAtm / 2, 0, 1);

  return { 0.5f, 1.0f, 0.5f, (float)pressureNorm };
}

std::string AtmoOverlay::getHint(const TileCoord& i_tileCoord) const
{
  const auto tile = d_location.getTile(i_tileCoord);
  if (tile)
  {
    const double pressureKPa = Units::paToKPa(tile->getVolumeUnit().getPressure());
    if (pressureKPa > 0)
      return "P: " + Sdk::toString(pressureKPa, 2) + " KPa";
  }

  return "Vacuum";
}
