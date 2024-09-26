#include "stdafx.h"
#include "DummyTileThd.h"

#include "GasThd.h"


namespace
{
  GasThd& getDummyGasThd()
  {
    static GasThd gasThd;
    return gasThd;
  }
} // anonym NS


std::vector<Dx::thd::IThdObject*> DummyTileThd::getThdObjectsAll() const
{
  auto& gasThd = getDummyGasThd();
  SAFE_DEREF(gasThd.getGasUnit()).clearGases();
  return { &gasThd };
}

std::vector<Dx::thd::IThdObject*> DummyTileThd::getThdObjectsExternal() const
{
  auto& gasThd = getDummyGasThd();
  SAFE_DEREF(gasThd.getGasUnit()).clearGases();
  return { &gasThd };
}
