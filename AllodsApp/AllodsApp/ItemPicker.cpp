#include "stdafx.h"
#include "ItemPicker.h"

#include "Location.h"
#include "Mount.h"
#include "MountUtils.h"
#include "Object.h"
#include "Prototypes.h"
#include "Session.h"
#include "Structure.h"
#include "TileUtils.h"

#include <LaggyDx/CursorUtils.h>


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
  if (const auto objectPtr = pickObject(i_screenPos))
    return objectPtr;
  
  if (const auto structureOrMountPtr = pickStructureOrMount(i_screenPos))
    return structureOrMountPtr;

  return nullptr;
}


EntityPtr ItemPicker::pickObject(const Sdk::Vector2I& i_screenPos) const
{
  const auto& location = SAFE_DEREF(d_session.getCurrentLocation());
  
  for (const auto objPtr : location.getObjects())
  {
    const auto& obj = SAFE_DEREF(objPtr);
    const auto rect = obj.getRect().move(-d_session.getCamera().getOffset());
    if (!rect.containsPoint(i_screenPos))
      continue;

    const auto& texture = SAFE_DEREF(obj.getObjectPrototype().texture);
    if (!texture.hasAlpha())
      return objPtr;
    
    if (texture.checkAlpha(i_screenPos - rect.topLeft(), obj.getAnimationPlayer().getCurrentFrame()))
      return objPtr;
  }

  return nullptr;
}

EntityPtr ItemPicker::pickStructureOrMount(const Sdk::Vector2I& i_screenPos) const
{
  const auto& location = SAFE_DEREF(d_session.getCurrentLocation());

  const auto tileCoords = TileUtils::getTileCoords(i_screenPos, d_session.getCamera());
  const auto tilePosScreen = TileUtils::getTilePosScreen(tileCoords, d_session.getCamera());
  const auto hitPos = i_screenPos - tilePosScreen;

  const auto* tile = location.getTile(tileCoords);
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
