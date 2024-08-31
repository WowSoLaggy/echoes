#include "stdafx.h"
#include "AtmoOverlay.h"

#include "Constants.h"
#include "Gases.h"
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

  const double pressurePa = tile->getUnit().getPressure();
  const double pressureAtm = Units::paToAtm(pressurePa);
  const double pressureNorm = Sdk::clamp<double>(pressureAtm / 2, 0, 1);

  return { 0.5f, 1.0f, 0.5f, (float)pressureNorm };
}

std::string AtmoOverlay::getHint(const TileCoord& i_tileCoord) const
{
  if (const auto tile = d_location.getTile(i_tileCoord))
  {
    const double pressurePa = tile->getUnit().getPressure();
    if (pressurePa >= Constants::MinimumPressure)
    {
      const auto gases = tile->getUnit().getGases();
      if (!gases.empty())
      {
        const int gasAmount = tile->getUnit().getGasAmount();
        CONTRACT_ASSERT(gasAmount > 0);

        std::string result = "P: " + Sdk::toString(Units::paToKPa(pressurePa), 2) + " KPa";
        for (const auto& [id, amount] : gases)
        {
          const double gasShare = amount / gasAmount;
          const std::string gasName = GasStr::toString(static_cast<Gas>(id));
          result += "\n" + gasName + ": " + Sdk::toString(gasShare * 100, 2) + "%";
        }

        return result;
      }
    }
  }

  return "Vacuum";
}
