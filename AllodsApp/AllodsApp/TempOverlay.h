#pragma once

#include "Fwd.h"
#include "IOverlay.h"

#include <LaggyDx/Gradient.h>


class TempOverlay : public IOverlay
{
public:
  TempOverlay(const Location& i_location);

  virtual OverlayType getType() const override;
  virtual Dx::Color getColor(const TileCoord& i_tileCoord) const override;

private:
  const Location& d_location;
  const Dx::Gradient d_gradient;
};
