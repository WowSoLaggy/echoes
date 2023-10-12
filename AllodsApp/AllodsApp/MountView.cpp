#include "stdafx.h"
#include "MountView.h"

#include "Constants.h"
#include "Fixture.h"
#include "Mount.h"
#include "MountUtils.h"
#include "Prototypes.h"

#include <LaggyDx/AnimatedSprite.h>
#include <LaggyDx/ISpriteShader.h>


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

  sprite.setRotation(MountUtils::getRotation(i_fixtureLocation));

  const auto basePosition = Sdk::Vector2I{ i_coords.x * Constants::TileSize, i_coords.y * Constants::TileSize };
  const auto mountPosition = basePosition + MountUtils::getPosition(sprite.getSize(), i_fixtureLocation);
  sprite.setPosition(mountPosition);

  sprite.setColor(std::move(i_color));

  d_shader.draw(sprite);
}
