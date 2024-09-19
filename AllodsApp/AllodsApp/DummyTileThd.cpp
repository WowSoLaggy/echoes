#include "stdafx.h"
#include "DummyTileThd.h"

#include "GasThd.h"


std::vector<Dx::thd::IThdObject*> DummyTileThd::getThdObjects() const
{
  static GasThd gasThd;
  SAFE_DEREF(gasThd.getGasUnit()).clearGases();
  return { &gasThd };
}
