#pragma once


enum class FixtureLocation
{
  Top,
  Right,
  Bottom,
  Left,

  Count
};

FixtureLocation rotateClockWise(FixtureLocation i_prevLocation);
