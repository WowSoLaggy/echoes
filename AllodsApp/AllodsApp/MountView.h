#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>


class MountView
{
public:
  MountView(const Dx::ISpriteShader& i_shader);

  void render(const Fixture& i_fixture, const TileCoord& i_coords) const;

private:
  const Dx::ISpriteShader& d_shader;
};
