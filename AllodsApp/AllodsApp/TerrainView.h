#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>


class TerrainView
{
public:
  explicit TerrainView(const Terrain& i_terrain, Dx::IRenderer2d& i_renderer);

  void update(double i_dt);
  void render() const;

private:
  const Terrain& d_terrain;
  Dx::IRenderer2d& d_renderer;
};
