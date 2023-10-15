#include "stdafx.h"
#include "FixtureLocations.h"


namespace
{
  const std::unordered_map<FixtureLocation, std::string> FixtureLocationStrings {
    { FixtureLocation::Top, "Top" },
    { FixtureLocation::Right, "Right" },
    { FixtureLocation::Bottom, "Bottom" },
    { FixtureLocation::Left, "Left" },
  };

} // anonym NS


DEFINE_ENUM_STR(FixtureLocation, FixtureLocationStrings)


FixtureLocation rotateClockWise(const FixtureLocation i_prevLocation)
{
  const auto newLocation = static_cast<FixtureLocation>(static_cast<int>(i_prevLocation) + 1);

  if (newLocation == FixtureLocation::Count)
    return FixtureLocation::Top;

  return newLocation;
}
