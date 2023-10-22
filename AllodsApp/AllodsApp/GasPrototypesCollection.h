#pragma once

#include "Gases.h"

#include <LaggyDx/LaggyDxFwd.h>


class GasPrototypesCollection
{
public:
  static void initialize();

  static const Dx::thd::GasPrototype& get(Gas i_gas);

private:
  GasPrototypesCollection() = delete;
};
