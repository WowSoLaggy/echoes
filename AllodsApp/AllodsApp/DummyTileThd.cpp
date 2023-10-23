#include "stdafx.h"
#include "DummyTileThd.h"

#include "Constants.h"


namespace
{
  Dx::thd::VolumeUnit createSpaceVolumeUnit()
  {
    Dx::thd::VolumeUnit volumeUnit;
    volumeUnit.setVolume(Constants::DefaultTileVolume);
    return volumeUnit;
  }

} // anonym NS


double DummyTileThd::getT() const
{
  return 0;
}

void DummyTileThd::setT(double i_t)
{
}


Dx::thd::VolumeUnit& DummyTileThd::getVolumeUnit()
{
  static auto volumeUnit = createSpaceVolumeUnit();
  volumeUnit.clear();
  return volumeUnit;
}

const Dx::thd::VolumeUnit& DummyTileThd::getVolumeUnit() const
{
  static const auto volumeUnit = createSpaceVolumeUnit();
  return volumeUnit;
}
