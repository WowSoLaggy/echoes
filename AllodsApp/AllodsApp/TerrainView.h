#pragma once

#include "Fwd.h"

#include <LaggyDx/ISpriteShader.h>
#include <LaggyDx/LaggyDxFwd.h>


class TerrainView
{
public:
  TerrainView(const Terrain& i_terrain);

  void update(double i_dt);
  void render() const;

private:
  const Terrain& d_terrain;
  std::unique_ptr<Dx::ISpriteShader> d_spriteShader;
};
