#include "stdafx.h"
#include "TileView.h"

#include "Constants.h"
#include "Structure.h"

#include <LaggyDx/AnimatedSprite.h>
#include <LaggyDx/App.h>
#include <LaggyDx/ISpriteShader.h>


namespace
{
  StructurePtr getTopStructure(const LayersMap& i_layers)
  {
    for (auto it = i_layers.rbegin(); it != i_layers.rend(); ++it)
    {
      if (it->second != nullptr)
        return it->second;
    }

    return nullptr;
  }

} // anonym NS


void TileView::render(const Dx::ISpriteShader& i_shader, const Tiles& i_tiles) const
{
  Dx::AnimatedSprite sprite;
  sprite.setSize({ Constants::TileSize, Constants::TileSize });

  for (const auto& [coord, tile] : i_tiles)
  {
    sprite.setPosition({ coord.x * Constants::TileSize, coord.y * Constants::TileSize });

    const auto& layers = tile.getLayers();
    auto it = std::prev(layers.cend());
    while (it != layers.cbegin())
    {
      const auto& structure = SAFE_DEREF(it->second);
      if (!structure.getPrototype().texture->hasAlpha())
        break;
      else
        --it;
    }

    for (; it != layers.cend(); ++it)
    {
      const auto& structure = SAFE_DEREF(it->second);

      sprite.setTexture(structure.getPrototype().texture);
      sprite.setCurrentFrame(structure.getAnimationPlayer().getCurrentFrame());

      i_shader.draw(sprite);
    }
  }
}
