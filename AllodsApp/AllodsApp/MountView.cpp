#include "stdafx.h"
#include "MountView.h"

#include "Constants.h"
#include "Fixture.h"
#include "Mount.h"
#include "Prototypes.h"

#include <LaggyDx/AnimatedSprite.h>
#include <LaggyDx/ISpriteShader.h>

#include <LaggySdk/Math.h>


namespace
{
  double getRotation(const FixtureLocation i_location)
  {
    const std::unordered_map<FixtureLocation, double> RotationsMap{
      { FixtureLocation::Bottom, 0 },
      { FixtureLocation::Top, Sdk::degToRad<double>(180) },
      { FixtureLocation::Left, Sdk::degToRad<double>(90) },
      { FixtureLocation::Right, Sdk::degToRad<double>(270) },
    };
    return RotationsMap.at(i_location);
  }

  Sdk::Vector2I getPosition(const Sdk::Vector2I& i_size, const FixtureLocation i_location)
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
}


MountView::MountView(const Dx::ISpriteShader& i_shader)
  : d_shader(i_shader)
{
}


void MountView::render(const Fixture& i_fixture, const TileCoord& i_coords) const
{
  for (const auto& [location, mountPtr] : i_fixture.getMounts())
  {
    if (mountPtr)
      render(i_coords, mountPtr->getMountPrototype().texture, location, mountPtr->getAnimationPlayer().getCurrentFrame());
  }
}

void MountView::render(
  const TileCoord& i_coords, const Dx::ITexture* i_texture,
  const FixtureLocation i_fixtureLocation, const int i_animationFrame,
  Dx::Color i_color) const
{
  Dx::AnimatedSprite sprite;

  sprite.setTexture(i_texture);
  sprite.setCurrentFrame(i_animationFrame);
  sprite.resetSizeToTexture();

  sprite.setRotation(getRotation(i_fixtureLocation));

  const auto basePosition = Sdk::Vector2I{ i_coords.x * Constants::TileSize, i_coords.y * Constants::TileSize };
  const auto mountPosition = basePosition + getPosition(sprite.getSize(), i_fixtureLocation);
  sprite.setPosition(mountPosition);

  sprite.setColor(std::move(i_color));

  d_shader.draw(sprite);
}
