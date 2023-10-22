#pragma once

#include <LaggyDx/LaggyDxFwd.h>


class GasPrototypesLoader
{
public:
  static Dx::thd::GasPrototypes loadAll();

private:
  GasPrototypesLoader() = delete;
};
