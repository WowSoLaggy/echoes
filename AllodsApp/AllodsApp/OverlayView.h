#pragma once

#include "Fwd.h"
#include "Tile.h"

#include <LaggyDx/LaggyDxFwd.h>


class OverlayView
{
public:
  void render(
    const Dx::ISpriteShader& i_shader,
    const Tiles& i_tiles,
    const IOverlay& i_overlay) const;
};
