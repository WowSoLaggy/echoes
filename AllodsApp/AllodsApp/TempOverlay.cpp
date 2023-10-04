#include "stdafx.h"
#include "TempOverlay.h"

#include "Location.h"


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
  const auto* tile = d_location.getTile(i_tileCoord);
  if (!tile)
    return { 0, 0, 0, 0 };

  const double t = tile->getT();
  const double normT = std::min<double>(100, std::max<double>(0, t));
  return d_gradient.get((float)normT / 100);
}
