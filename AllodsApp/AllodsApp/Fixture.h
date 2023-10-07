#pragma once

#include "FixtureLocations.h"
#include "Fwd.h"

using FixturesMap = std::unordered_map<FixtureLocation, StructurePtr>;

class Fixture
{
public:
  Fixture();

  StructurePtr getMount(FixtureLocation i_location) const;
  void setMount(FixtureLocation i_location, StructurePtr i_structure);

private:
  FixturesMap d_mounts;
};

using FixturePtr = std::shared_ptr<Fixture>;
