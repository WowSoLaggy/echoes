#include "stdafx.h"
#include "Units.h"

#include "Constants.h"


namespace Units
{
  double paToKPa(const double i_pa)
  {
    return i_pa / 1000.0;
  }

  double paToAtm(const double i_pa)
  {
    return i_pa / Constants::PaInOneAtm;
  }


  double volumeToLitres(const double i_volume)
  {
    return i_volume * 1000;
  }


  double celsiusToKelvin(const double i_celsius)
  {
    return i_celsius + Constants::KelvinOffset;
  }

  double kelvinToCelsius(const double i_kelvin)
  {
    return i_kelvin - Constants::KelvinOffset;
  }

} // ns Units
