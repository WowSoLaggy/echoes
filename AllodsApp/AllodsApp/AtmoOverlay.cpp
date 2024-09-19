#include "stdafx.h"
#include "AtmoOverlay.h"

#include "Constants.h"
#include "Gases.h"
#include "Location.h"
#include "Units.h"

#include <LaggySdk/Math.h>
#include <LaggySdk/StringUtils.h>


namespace
{
  // Map of colors for gases
  std::unordered_map<Gas, Dx::Color> gasColors = {
    { Gas::Oxygen, { 0.0f, 0.0f, 1.0f, 1.0f } },
    { Gas::CarbonDioxide, { 1.0f, 0.5f, 0.0f, 1.0f } },
  };

  // Get color from gas mixture
  Dx::Color getColorFromGasMixture(const Dx::thd::GasUnit& i_gasUnit)
  {
    const auto& gases = i_gasUnit.getGases();
    if (gases.empty())
      return { 0, 0, 0, 0 };

    Dx::Color resultColor;
    const double totalAmount = i_gasUnit.getGasAmount();
    for (const auto& [id, amount] : gases)
    {
      const double gasShare = (double)amount / totalAmount;
      const auto& color = gasColors[static_cast<Gas>(id)];
      resultColor += color * (float)gasShare;
    }

    const double pressurePa = i_gasUnit.getPressure();
    const double pressureAtm = Units::paToAtm(pressurePa);
    const double pressureNorm = Sdk::clamp<double>(pressureAtm / 2, 0, 1);
    resultColor.a = (float)pressureNorm;

    return resultColor;
  }
} // anonym NS


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

  return getColorFromGasMixture(SAFE_DEREF(tile->getGasUnitThd().getGasUnit()));
}

std::string AtmoOverlay::getHint(const TileCoord& i_tileCoord) const
{
  if (const auto tile = d_location.getTile(i_tileCoord))
  {
    const auto& gasUnit = SAFE_DEREF(tile->getGasUnitThd().getGasUnit());

    const double pressurePa = gasUnit.getPressure();
    if (pressurePa >= Constants::MinimumPressure)
    {
      const auto gases = gasUnit.getGases();
      if (!gases.empty())
      {
        const int gasAmount = gasUnit.getGasAmount();
        CONTRACT_ASSERT(gasAmount > 0);

        std::string result = "P: " + Sdk::toString(Units::paToKPa(pressurePa), 2) + " KPa";
        for (const auto& [id, amount] : gases)
        {
          const double gasShare = (double)amount / gasAmount;
          const std::string gasName = GasStr::toString(static_cast<Gas>(id));
          result += "\n" + gasName + ": " + Sdk::toString(gasShare * 100, 2) + "%";
        }

        return result;
      }
    }
  }

  return "Vacuum";
}
