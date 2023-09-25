#include "stdafx.h"
#include "StructureUtils.h"

#include "Session.h"
#include "Structure.h"
#include "TileUtils.h"

#include <LaggyDx/CursorUtils.h>


StructurePtr StructureUtils::getStructureUnderCursor(const Session& i_session)
{
  const auto* location = i_session.getLocation();
  if (!location)
    return nullptr;

  const auto& mousePosScreen = Dx::CursorUtils::getPosition();
  const auto tileCoords = TileUtils::getTileCoords(mousePosScreen, i_session.getCamera());
  const auto tilePosScreen = TileUtils::getTilePosScreen(tileCoords, i_session.getCamera());
  const auto hitPos = mousePosScreen - tilePosScreen;

  auto* tile = location->getTile(tileCoords);
  if (!tile)
    return nullptr;

  for (const auto& [_, structurePtr] : std::ranges::reverse_view(tile->getLayers()))
  {
    auto& structure = SAFE_DEREF(structurePtr);
    auto& texture = SAFE_DEREF(structure.getPrototype().texture);
    if (!texture.hasAlpha())
      return structurePtr;

    if (texture.checkAlpha(hitPos, structure.getAnimationPlayer().getCurrentFrame()))
      return structurePtr;
  }

  return nullptr;
}
