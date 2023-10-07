#include "stdafx.h"
#include "Fixture.h"


Fixture::Fixture()
{
  for (int i = 0; i < static_cast<int>(FixtureLocation::Count); ++i)
    d_mounts[static_cast<FixtureLocation>(i)] = nullptr;
}


StructurePtr Fixture::getMount(const FixtureLocation i_location) const
{
  return d_mounts.at(i_location);
}

void Fixture::setMount(FixtureLocation i_location, StructurePtr i_structure)
{
  d_mounts[i_location] = i_structure;
}
