#include "stdafx.h"
#include "OverlayView.h"

#include "Constants.h"
#include "IOverlay.h"

#include <LaggyDx/ISpriteShader.h>
#include <LaggyDx/Sprite.h>
#include <LaggyDx/TextureUtils.h>


void OverlayView::render(
  const Dx::ISpriteShader& i_shader,
  const Tiles& i_tiles,
  const IOverlay& i_overlay) const
{
  Dx::Sprite sprite;
  sprite.setSize({ Constants::TileSize, Constants::TileSize });

  for (const auto& [coord, tile] : i_tiles)
  {
    sprite.setPosition({ coord.x * Constants::TileSize, coord.y * Constants::TileSize });
    sprite.setTexture(Dx::TextureUtils::getTexture("White.png"));
    sprite.setColor(i_overlay.getColor(coord));

    i_shader.draw(sprite);
  }
}
