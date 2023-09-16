#pragma once

#include "Tile.h"

#include <LaggyDx/LaggyDxFwd.h>


class TileView
{
public:
  void render(const Dx::ISpriteShader& i_shader, const Tiles& i_tiles) const;
};
