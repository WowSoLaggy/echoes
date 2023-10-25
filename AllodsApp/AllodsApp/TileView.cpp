#include "stdafx.h"
#include "TileView.h"

#include "Avatar.h"
#include "AvatarView.h"
#include "Constants.h"
#include "MountView.h"
#include "Object.h"
#include "ObjectView.h"
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
  for (const auto& [coord, tilePtr] : i_tiles)
  {
    renderLayers(i_shader, SAFE_DEREF(tilePtr), coord);
    renderObjects(i_shader, SAFE_DEREF(tilePtr));
    renderAvatars(i_shader, SAFE_DEREF(tilePtr));
  }
}


void TileView::renderLayers(const Dx::ISpriteShader& i_shader, const Tile& i_tile, const TileCoord& i_tileCoord) const
{
  const MountView mountView(i_shader);
  const StructureView structureView(i_shader);

  const auto& layers = i_tile.getLayers();
  if (layers.empty())
    return;

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
      structure.getPrototype().texture, { i_tileCoord.x * Constants::TileSize, i_tileCoord.y * Constants::TileSize },
      structure.getAnimationPlayer().getCurrentFrame());

    if (const auto fixturePtr = structure.getFixture())
      mountView.render(*fixturePtr, i_tileCoord);
  }
}

void TileView::renderObjects(const Dx::ISpriteShader& i_shader, const Tile& i_tile) const
{
  const ObjectView objectView(i_shader);

  for (const auto objectPtr : i_tile.getObjects())
  {
    const auto& object = SAFE_DEREF(objectPtr);
    objectView.render(object.getPrototype().texture, object.getPosition(), object.getAnimationPlayer().getCurrentFrame());
  }
}

void TileView::renderAvatars(const Dx::ISpriteShader& i_shader, const Tile& i_tile) const
{
  const AvatarView avatarView(i_shader);

  for (const auto avatarPtr : i_tile.getAvatars())
  {
    const auto& avatar = SAFE_DEREF(avatarPtr);
    avatarView.render(avatar.getPrototype().texture, avatar.getPosition(), avatar.getAnimationPlayer().getCurrentFrame());
  }
}
