#include "stdafx.h"
#include "Fixture.h"

#include "Mount.h"


Fixture::Fixture()
{
  for (int i = 0; i < static_cast<int>(FixtureLocation::Count); ++i)
    d_mounts[static_cast<FixtureLocation>(i)] = nullptr;
}


void Fixture::pushFields()
{
  for (auto& [location, mountPtr] : d_mounts)
    pushSharedPtr(FixtureLocationStr::toString(location), mountPtr);
}


const FixturesMap& Fixture::getMounts() const
{
  return d_mounts;
}

MountPtr Fixture::getMount(const FixtureLocation i_location) const
{
  return d_mounts.at(i_location);
}


void Fixture::setMount(const FixtureLocation i_location, MountPtr i_mount)
{
  CONTRACT_EXPECT(!d_mounts[i_location]);
  d_mounts[i_location] = i_mount;
}

void Fixture::resetMount(const FixtureLocation i_location)
{
  d_mounts[i_location] = nullptr;
}
