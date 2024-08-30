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


std::optional<double> DummyTileThd::getT() const
{
  return std::nullopt;
}

void DummyTileThd::setT(double i_t)
{
}


double DummyTileThd::getInsulationFactor() const
{
  return 0.01; // almost perfect insulation
}

bool DummyTileThd::isAirTight() const
{
  return false;
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
