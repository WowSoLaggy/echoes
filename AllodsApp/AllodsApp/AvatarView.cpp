#include "stdafx.h"
#include "AvatarView.h"

#include <LaggyDx/AnimatedSprite.h>
#include <LaggyDx/ISpriteShader.h>


AvatarView::AvatarView(const Dx::ISpriteShader& i_shader)
  : d_shader(i_shader)
{
}


void AvatarView::render(
  const Dx::ITexture* i_texture, const Sdk::Vector2I& i_position,
  int i_animationFrame, Dx::Color i_color) const
{
  Dx::AnimatedSprite sprite;

  sprite.setTexture(i_texture);
  sprite.resetSizeToTexture();
  sprite.setCurrentFrame(i_animationFrame);
  sprite.setColor(std::move(i_color));

  const auto pos = i_position - sprite.getSize() / 2;
  sprite.setPosition(pos);

  d_shader.draw(sprite);
}
