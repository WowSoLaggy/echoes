#include "stdafx.h"
#include "EntityUtils.h"

#include "Mount.h"
#include "MountUtils.h"
#include "Prototypes.h"
#include "Session.h"
#include "Structure.h"
#include "TileUtils.h"

#include <LaggyDx/CursorUtils.h>


EntityPtr EntityUtils::getEntityUnderCursor(const Session& i_session)
{
  const auto* location = i_session.getCurrentLocation();
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

    if (const auto fixturePtr = structure.getFixture())
    {
      if (auto mountPtr = MountUtils::getHitMount(*fixturePtr, hitPos))
        return mountPtr;
    }

    auto& texture = SAFE_DEREF(structure.getPrototype().texture);
    if (!texture.hasAlpha())
      return structurePtr;

    if (texture.checkAlpha(hitPos, structure.getAnimationPlayer().getCurrentFrame()))
      return structurePtr;
  }

  return nullptr;
}
