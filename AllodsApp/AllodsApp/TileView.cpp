#include "stdafx.h"
#include "TileView.h"

#include "Constants.h"
#include "MountView.h"
#include "Prototypes.h"
#include "Structure.h"
#include "StructureView.h"

#include <LaggyDx/App.h>


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
  const MountView mountView(i_shader);
  const StructureView structureView(i_shader);

  for (const auto& [coord, tilePtr] : i_tiles)
  {
    const auto& layers = SAFE_DEREF(tilePtr).getLayers();
    if (layers.empty())
      continue;

    auto it = std::prev(layers.cend());
    while (it != layers.cbegin())
    {
      const auto& structure = SAFE_DEREF(it->second);
      const auto& texture = SAFE_DEREF(structure.getPrototype().texture);
      if (!texture.hasAlpha())
        break;
      else
        --it;
    }

    for (; it != layers.cend(); ++it)
    {
      const auto& structure = SAFE_DEREF(it->second);

      structureView.render(
        structure.getPrototype().texture, { coord.x * Constants::TileSize, coord.y * Constants::TileSize },
        structure.getAnimationPlayer().getCurrentFrame());

      if (const auto fixturePtr = structure.getFixture())
        mountView.render(*fixturePtr, coord);
    }
  }
}
