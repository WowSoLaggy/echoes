#include "stdafx.h"
#include "OverlayView.h"

#include "Constants.h"
#include "IOverlay.h"

#include <LaggyDx/ISpriteShader.h>
#include <LaggyDx/Sprite.h>


void OverlayView::render(
  const Dx::ISpriteShader& i_shader,
  const Tiles& i_tiles,
  const IOverlay& i_overlay) const
{
  Dx::Sprite sprite;
  sprite.setSize({ (float)Constants::TileSize, (float)Constants::TileSize });

  for (const auto& [coord, tile] : i_tiles)
  {
    sprite.setPosition({ (float)(coord.x * Constants::TileSize), (float)(coord.y * Constants::TileSize) });
    sprite.setTexture("white.png");
    sprite.setColor(i_overlay.getColor(coord));

    i_shader.draw(sprite);
  }
}
