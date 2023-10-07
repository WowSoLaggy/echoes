#pragma once

#include "FixtureLocations.h"
#include "Fwd.h"

using FixturesMap = std::unordered_map<FixtureLocation, MountPtr>;

class Fixture
{
public:
  Fixture();

  const FixturesMap& getMounts() const;
  MountPtr getMount(FixtureLocation i_location) const;

  void setMount(FixtureLocation i_location, MountPtr i_mount);
  void resetMount(FixtureLocation i_location);

private:
  FixturesMap d_mounts;
};
