#pragma once

#include <LaggySdk/EnumStr.h>


enum class FixtureLocation
{
  Top,
  Right,
  Bottom,
  Left,

  Count
};


DECLARE_ENUM_STR(FixtureLocation)


FixtureLocation rotateClockWise(FixtureLocation i_prevLocation);
