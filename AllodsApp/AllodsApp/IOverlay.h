#pragma once

#include "Fwd.h"
#include "OverlayTypes.h"

#include <LaggyDx/Colors.h>


class IOverlay
{
public:
  static std::unique_ptr<IOverlay> create(OverlayType i_overlayType, const Location& i_location);

public:
  virtual ~IOverlay() = default;

  virtual OverlayType getType() const = 0;

  virtual Dx::Color getColor(const TileCoord& i_tileCoord) const = 0;
  virtual std::string getHint(const TileCoord& i_tileCoord) const = 0;
};
