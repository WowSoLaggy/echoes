#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>


class TerrainView
{
public:
  TerrainView(const Terrain& i_terrain);

  void update(double i_dt);
  void render(const Dx::ISpriteShader& i_shader) const;

private:
  const Terrain& d_terrain;
};
