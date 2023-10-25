#include "stdafx.h"
#include "DummyTileThd.h"

#include "Constants.h"

#include <LaggyDx/Unit.h>


namespace
{
  Dx::thd::Unit createSpaceUnit()
  {
    Dx::thd::Unit unit;
    unit.setVolume(Constants::DefaultTileVolume);
    return unit;
  }

} // anonym NS


double DummyTileThd::getT() const
{
  return 0;
}

void DummyTileThd::setT(double i_t)
{
}


Dx::thd::Unit& DummyTileThd::getUnit()
{
  static auto unit = createSpaceUnit();
  unit.clear();
  return unit;
}

const Dx::thd::Unit& DummyTileThd::getUnit() const
{
  static const auto unit = createSpaceUnit();
  return unit;
}
