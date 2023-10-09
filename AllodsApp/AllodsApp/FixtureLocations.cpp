#include "stdafx.h"
#include "FixtureLocations.h"


FixtureLocation rotateClockWise(const FixtureLocation i_prevLocation)
{
  const auto newLocation = static_cast<FixtureLocation>(static_cast<int>(i_prevLocation) + 1);

  if (newLocation == FixtureLocation::Count)
    return FixtureLocation::Top;

  return newLocation;
}
