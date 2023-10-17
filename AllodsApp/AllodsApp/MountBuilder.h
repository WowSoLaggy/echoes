#pragma once

#include "FixtureLocations.h"
#include "Fwd.h"


class MountBuilder
{
public:
  MountBuilder(
    Location& i_location, const TileCoord& i_tileCoords,
    PrototypePtr i_prototype, FixtureLocation i_fixtureLocation);

  bool canBeBuilt() const;
  void build() const;

private:
  Location& d_location;
  const TileCoord& d_tileCoords;
  PrototypePtr d_prototype;
  const FixtureLocation d_fixtureLocation;

  StructurePtr getStructureWithFixture() const;
};
