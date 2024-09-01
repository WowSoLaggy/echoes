#pragma once

namespace Constants
{
  constexpr int TileSize = 64;

  constexpr double DefaultTileVolume = 1;

  constexpr double PaInOneAtm = 101325;
  constexpr double IdeatHeatTransferPressure = PaInOneAtm * 2;
  constexpr double BaseAirInsulation = 0.9;
  constexpr double MinimumPressure = 2;

  constexpr double KelvinOffset = 273.15;
  constexpr double MbrTemperature = 2.7; // temperature that equals to the cosmic microwave background radiation

  constexpr double GasInSpaceDecayFactor = 0.1;

  constexpr double VacuumThermalConductivity = 0;
  constexpr double VacuumHeatCapacity = 1000000;

} // ns Constants
