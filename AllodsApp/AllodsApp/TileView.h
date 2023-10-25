#pragma once

#include "Tile.h"

#include <LaggyDx/LaggyDxFwd.h>


class TileView
{
public:
  void render(const Dx::ISpriteShader& i_shader, const Tiles& i_tiles) const;

private:
  void renderLayers(const Dx::ISpriteShader& i_shader, const Tile& i_tile, const TileCoord& i_tileCoord) const;
  void renderObjects(const Dx::ISpriteShader& i_shader, const Tile& i_tile) const;
  void renderAvatars(const Dx::ISpriteShader& i_shader, const Tile& i_tile) const;
};
