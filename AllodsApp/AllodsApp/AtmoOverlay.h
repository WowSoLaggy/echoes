#pragma once

#include "Fwd.h"
#include "IOverlay.h"


class AtmoOverlay : public IOverlay
{
public:
  AtmoOverlay(const Location& i_location);

  virtual OverlayType getType() const override;

  virtual Dx::Color getColor(const TileCoord& i_tileCoord) const override;
  virtual std::string getHint(const TileCoord& i_tileCoord) const override;

private:
  const Location& d_location;
};
