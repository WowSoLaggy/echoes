#include "stdafx.h"
#include "GasPrototypesCollection.h"

#include "GasPrototypesLoader.h"

#include <LaggyDx/GasPrototype.h>


namespace
{
  std::unordered_map<std::string, Dx::thd::GasPrototypePtr> g_prototypes;

} // anonym NS


void GasPrototypesCollection::initialize()
{
  const auto prototypes = GasPrototypesLoader::loadAll();
  for (const auto& prototypePtr : prototypes)
  {
    const auto& prototype = SAFE_DEREF(prototypePtr);
    g_prototypes.insert({ prototype.name, prototypePtr });
  }
}


const Dx::thd::GasPrototype& GasPrototypesCollection::get(const Gas i_gas)
{
  return SAFE_DEREF(g_prototypes.at(GasStr::toString(i_gas)));
}
