#include "stdafx.h"
#include "StructureView.h"

#include <LaggyDx/AnimatedSprite.h>
#include <LaggyDx/ISpriteShader.h>


StructureView::StructureView(const Dx::ISpriteShader& i_shader)
  : d_shader(i_shader)
{
}


void StructureView::render(
  const Dx::ITexture* i_texture, Sdk::Vector2F i_position,
  int i_animationFrame, Dx::Color i_color) const
{
  Dx::AnimatedSprite sprite;

  sprite.setTexture(i_texture);
  sprite.resetSizeToTexture();
  sprite.setPosition(std::move(i_position));
  sprite.setColor(std::move(i_color));
  sprite.setCurrentFrame(i_animationFrame);

  d_shader.draw(sprite);
}
