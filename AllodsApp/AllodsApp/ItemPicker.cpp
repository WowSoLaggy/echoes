#include "stdafx.h"
#include "ItemPicker.h"

#include "Avatar.h"
#include "Location.h"
#include "Mount.h"
#include "MountUtils.h"
#include "Object.h"
#include "Prototypes.h"
#include "Session.h"
#include "Structure.h"
#include "TileUtils.h"

#include <LaggyDx/CursorUtils.h>


namespace
{
  std::vector<TilePtr> collectNeighborTiles(const TileCoord& i_coord, const Location& i_location)
  {
    std::vector<TilePtr> tiles;

    for (int y = -1; y <= 1; ++y)
    {
      for (int x = -1; x <= 1; ++x)
        tiles.push_back(i_location.getTile(i_coord + TileCoord{ x, y }));
    }

    return tiles;
  }

  EntityPtr pickEntity(const auto& i_entities, const Sdk::Vector2I& i_screenPos, const Sdk::Vector2I& i_cameraOffset)
  {
    for (const auto& objPtr : i_entities)
    {
      const auto& obj = SAFE_DEREF(objPtr);
      const auto rect = obj.getRect().move(-i_cameraOffset);
      if (!rect.containsPoint(i_screenPos))
        continue;

      const auto& texture = SAFE_DEREF(obj.getPrototype().texture);
      if (!texture.hasAlpha())
        return objPtr;

      if (texture.checkAlpha(i_screenPos - rect.topLeft(), obj.getAnimationPlayer().getCurrentFrame()))
        return objPtr;
    }

    return nullptr;
  }

} // anonym NS


ItemPicker::ItemPicker(const Session& i_session)
  : d_session(i_session)
{
}


EntityPtr ItemPicker::pick() const
{
  return pick(Dx::CursorUtils::getPosition());
}

EntityPtr ItemPicker::pick(const Sdk::Vector2I& i_screenPos) const
{
  if (const auto avatarPtr = pickAvatar(i_screenPos))
    return avatarPtr;

  if (const auto objectPtr = pickObject(i_screenPos))
    return objectPtr;
  
  if (const auto structureOrMountPtr = pickStructureOrMount(i_screenPos))
    return structureOrMountPtr;

  return nullptr;
}


EntityPtr ItemPicker::pickAvatar(const Sdk::Vector2I& i_screenPos) const
{
  const auto& location = SAFE_DEREF(d_session.getCurrentLocation());
  const auto tileCoord = TileUtils::getTileCoords(i_screenPos, d_session.getCamera());
  const auto tilesToCheck = collectNeighborTiles(tileCoord, location);
  for (const auto tile : tilesToCheck)
  {
    if (!tile)
      continue;

    if (const auto entityPtr = pickEntity(tile->getAvatars(), i_screenPos, d_session.getCamera().getOffset()))
      return entityPtr;
  }

  return nullptr;
}

EntityPtr ItemPicker::pickObject(const Sdk::Vector2I& i_screenPos) const
{
  const auto& location = SAFE_DEREF(d_session.getCurrentLocation());
  const auto tileCoord = TileUtils::getTileCoords(i_screenPos, d_session.getCamera());
  const auto tilesToCheck = collectNeighborTiles(tileCoord, location);
  for (const auto tile : tilesToCheck)
  {
    if (!tile)
      continue;

    if (const auto entityPtr = pickEntity(tile->getObjects(), i_screenPos, d_session.getCamera().getOffset()))
      return entityPtr;
  }

  return nullptr;
}

EntityPtr ItemPicker::pickStructureOrMount(const Sdk::Vector2I& i_screenPos) const
{
  const auto& location = SAFE_DEREF(d_session.getCurrentLocation());

  const auto tileCoords = TileUtils::getTileCoords(i_screenPos, d_session.getCamera());
  const auto tilePosScreen = TileUtils::getTilePosScreen(tileCoords, d_session.getCamera());
  const auto hitPos = i_screenPos - tilePosScreen;

  const auto tile = location.getTile(tileCoords);
  if (!tile)
    return nullptr;

  for (const auto& [_, structurePtr] : std::ranges::reverse_view(tile->getLayers()))
  {
    const auto& structure = SAFE_DEREF(structurePtr);

    if (const auto fixturePtr = structure.getFixture())
    {
      if (auto mountPtr = MountUtils::getHitMount(*fixturePtr, hitPos))
        return mountPtr;
    }

    const auto& texture = SAFE_DEREF(structure.getPrototype().texture);
    if (!texture.hasAlpha())
      return structurePtr;

    if (texture.checkAlpha(hitPos, structure.getAnimationPlayer().getCurrentFrame()))
      return structurePtr;
  }

  return nullptr;
}
