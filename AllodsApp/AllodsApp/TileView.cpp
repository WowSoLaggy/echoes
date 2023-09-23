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
  const auto& rc = Dx::App::get().getResourceController();

  Dx::AnimatedSprite sprite;
  sprite.setSize({ Constants::TileSize, Constants::TileSize });

  for (const auto& [coord, tile] : i_tiles)
  {
    const auto& layers = tile.getLayers();
    const auto topStructure = getTopStructure(layers);
    if (topStructure == nullptr)
      continue;

    const auto& prototype = topStructure->getPrototype();
    const auto& texture = rc.getTexture(prototype.textureName);

    sprite.setTexture(texture);
    sprite.setPosition({ coord.x * Constants::TileSize, coord.y * Constants::TileSize });

    i_shader.draw(sprite);
  }
}
