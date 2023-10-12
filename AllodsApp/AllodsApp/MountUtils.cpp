#include "stdafx.h"
#include "MountUtils.h"

#include "Constants.h"
#include "Fixture.h"
#include "Mount.h"

#include <LaggySdk/Math.h>


MountPtr MountUtils::getHitMount(const Fixture& i_fixture, const Sdk::Vector2I& i_hitPos)
{
  for (const auto& [loc, mountPtr] : i_fixture.getMounts())
  {
    if (!mountPtr)
      continue;

    const auto rect = getRect(mountPtr->getSize(), loc);
    if (rect.containsPoint(i_hitPos))
      return mountPtr;
  }

  return nullptr;
}


double MountUtils::getRotation(const FixtureLocation i_location)
{
  const std::unordered_map<FixtureLocation, double> RotationsMap{
    { FixtureLocation::Bottom, 0 },
    { FixtureLocation::Top, Sdk::degToRad<double>(180) },
    { FixtureLocation::Left, Sdk::degToRad<double>(90) },
    { FixtureLocation::Right, Sdk::degToRad<double>(270) },
  };
  return RotationsMap.at(i_location);
}

Sdk::Vector2I MountUtils::getPosition(const Sdk::Vector2I& i_size, const FixtureLocation i_location)
{
  Sdk::Vector2I pos;

  switch (i_location)
  {
  case FixtureLocation::Bottom:
  {
    pos.x = (Constants::TileSize - i_size.x) / 2;
    pos.y = Constants::TileSize - i_size.y;
    break;
  }
  case FixtureLocation::Top:
  {
    pos.x = (Constants::TileSize - i_size.x) / 2 + i_size.x;
    pos.y = i_size.y;
    break;
  }
  case FixtureLocation::Left:
  {
    pos.x = i_size.y;
    pos.y = (Constants::TileSize - i_size.x) / 2;
    break;
  }
  case FixtureLocation::Right:
  {
    pos.x = Constants::TileSize - i_size.y;
    pos.y = (Constants::TileSize - i_size.x / 2);
    break;
  }
  }

  return pos;
}

Sdk::RectI MountUtils::getRect(const Sdk::Vector2I& i_size, const FixtureLocation i_location)
{
  const auto p1 = getPosition(i_size, i_location);
  auto p2 = i_size;
  p2.rotate(getRotation(i_location));
  return { p1, p1 + p2 };
}
