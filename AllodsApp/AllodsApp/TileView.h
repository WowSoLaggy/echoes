#pragma once

#include "Tile.h"

#include <LaggyDx/LaggyDxFwd.h>


class TileView
{
public:
  void render(const Dx::ISpriteShader& i_shader, const TileCoord& i_coord, const Tile& i_tile) const;
};
