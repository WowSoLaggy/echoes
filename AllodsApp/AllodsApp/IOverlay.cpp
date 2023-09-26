#include "stdafx.h"
#include "IOverlay.h"

#include "AtmoOverlay.h"
#include "TempOverlay.h"


std::unique_ptr<IOverlay> IOverlay::create(const OverlayType i_overlayType, const Location& i_location)
{
  if (i_overlayType == OverlayType::Atmo)
    return std::make_unique<AtmoOverlay>(i_location);
  else if (i_overlayType == OverlayType::Temp)
    return std::make_unique<TempOverlay>(i_location);

  return nullptr;
}
