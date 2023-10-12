#pragma once

#include "FixtureLocations.h"
#include "Fwd.h"

#include <LaggySdk/Rect.h>
#include <LaggySdk/Vector.h>


class MountUtils
{
public:
  static MountPtr getHitMount(const Fixture& i_fixture, const Sdk::Vector2I& i_hitPos);

  static double getRotation(const FixtureLocation i_location);
  static Sdk::Vector2I getPosition(const Sdk::Vector2I& i_size, const FixtureLocation i_location);
  static Sdk::RectI getRect(const Sdk::Vector2I& i_size, const FixtureLocation i_location);

private:
  MountUtils() = delete;
};
