#include "stdafx.h"
#include "TempOverlay.h"

#include "Entity.h"
#include "Location.h"
#include "Prototypes.h"
#include "Units.h"

#include <LaggySdk/Math.h>
#include <LaggySdk/StringUtils.h>


namespace
{
  const float DefaultOverlayAlpha = 0.5f;

} // anonym NS


TempOverlay::TempOverlay(const Location& i_location)
  : d_location(i_location)
  , d_gradient(
    Dx::colorWithAlpha(Dx::Colors::LightBlue, DefaultOverlayAlpha),
    Dx::colorWithAlpha(Dx::Colors::Red, DefaultOverlayAlpha))
{
}


OverlayType TempOverlay::getType() const
{
  return OverlayType::Temp;
}


Dx::Color TempOverlay::getColor(const TileCoord& i_tileCoord) const
{
  const auto tile = d_location.getTile(i_tileCoord);
  if (!tile)
    return { 0, 0, 0, 0 };

  const auto tOpt = tile->getTemperature();
  if (!tOpt)
    return { 0, 0, 0, 0 };

  const double normT = Sdk::clamp<double>(*tOpt, 0, 100);
  return d_gradient.get((float)normT / 100);
}

std::string TempOverlay::getHint(const TileCoord& i_tileCoord) const
{
  const auto str = [](const std::optional<double> i_tempK) -> std::string
  {
    if (!i_tempK)
      return "N/A";
    else
      return Sdk::toString(Units::kelvinToCelsius(*i_tempK), 1) + " C";
  };

  const auto tile = d_location.getTile(i_tileCoord);
  if (!tile)
    return "T: N/A";

  std::string hint = "Atmo: " + str(tile->getTemperature());

  for (const auto& entityPtr : tile->getEntities())
  {
    const auto& entity = SAFE_DEREF(entityPtr);
    hint += "\n" + entity.getPrototype().name + ": " + str(entity.getTemperature());
  }

  return hint;
}
