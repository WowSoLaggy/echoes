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


  double volumeToLitres(double i_volume)
  {
    return i_volume * 1000;
  }

} // ns Units
