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


std::optional<double> DummyTileThd::getTemperature() const
{
  return std::nullopt;
}

void DummyTileThd::setTemperature(double i_t)
{
}

double DummyTileThd::getThermalConductivity() const
{
  return Constants::VacuumThermalConductivity;
}

double DummyTileThd::getHeatCapacity() const
{
  return Constants::VacuumHeatCapacity;
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


std::vector<Dx::thd::IThdObject*> DummyTileThd::getHeatAgents() const
{
  return {};
}
