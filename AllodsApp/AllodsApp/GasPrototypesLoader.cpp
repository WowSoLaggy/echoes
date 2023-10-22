#include "stdafx.h"
#include "GasPrototypesLoader.h"

#include "Gases.h"

#include <LaggyDx/GasPrototype.h>


Dx::thd::GasPrototypes GasPrototypesLoader::loadAll()
{
  Dx::thd::GasPrototypes prototypes;

  // Oxygen
  {
    auto proto = std::make_shared<Dx::thd::GasPrototype>();
    proto->name = GasStr::toString(Gas::Oxygen);
    prototypes.push_back(std::move(proto));
  }

  // CarbonDioxide
  {
    auto proto = std::make_shared<Dx::thd::GasPrototype>();
    proto->name = GasStr::toString(Gas::CarbonDioxide);
    prototypes.push_back(std::move(proto));
  }

  return prototypes;
}
