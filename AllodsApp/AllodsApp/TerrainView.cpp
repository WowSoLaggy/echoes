#include "stdafx.h"
#include "TerrainView.h"

#include "Terrain.h"
#include "TerrainTextures.h"

#include <LaggyDx/AnimatedSprite.h>
#include <LaggyDx/App.h>
#include <LaggyDx/ISpriteShader.h>


TerrainView::TerrainView(const Terrain& i_terrain)
  : d_terrain(i_terrain)
{
}


void TerrainView::update(double i_dt)
{
}

void TerrainView::render(const Dx::ISpriteShader& i_shader) const
{
  constexpr int TileSize = 64;
  const auto& rc = Dx::App::get().getResourceController();

  Dx::AnimatedSprite sprite;
  sprite.setSize({ TileSize, TileSize });
  for (int y = 0; y < d_terrain.getSizeY(); ++y)
  {
    for (int x = 0; x < d_terrain.getSizeX(); ++x)
    {
      const auto terrainType = d_terrain.getTerrainType(x, y);
      const auto& terrainTextureName = getTerrainTexture(terrainType);
      const auto& texture = rc.getTexture(terrainTextureName);
      sprite.setTexture(texture);

      sprite.setPosition({ x * TileSize, y * TileSize });

      i_shader.draw(sprite);
    }
  }
}
