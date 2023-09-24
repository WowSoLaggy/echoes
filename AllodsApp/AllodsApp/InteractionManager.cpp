#include "stdafx.h"
#include "InteractionManager.h"

#include "Session.h"
#include "Structure.h"
#include "TileUtils.h"

#include <LaggyDx/CursorUtils.h>


InteractionManager::InteractionManager(Session& i_session)
  : d_session(i_session)
{
}


bool InteractionManager::onMouseClick(Dx::MouseKey i_key)
{
  const auto behaviorModel = getInteractionBehaviorModel();
  if (!behaviorModel)
    return false;

  behaviorModel->interact();

  return true;
}


BehaviorModelPtr InteractionManager::getInteractionBehaviorModel() const
{
  const auto* world = d_session.getWorld();
  if (!world)
    return nullptr;

  const auto& mousePosScreen = Dx::CursorUtils::getPosition();
  const auto tileCoords = getTileCoords(mousePosScreen, d_session.getCamera());
  const auto tilePosScreen = getTilePosScreen(tileCoords, d_session.getCamera());
  const auto hitPos = mousePosScreen - tilePosScreen;

  auto* tile = world->getTile(tileCoords);
  if (!tile)
    return nullptr;

  for (const auto& [_, structurePtr] : std::ranges::reverse_view(tile->getLayers()))
  {
    auto& structure = SAFE_DEREF(structurePtr);
    auto& texture = SAFE_DEREF(structure.getPrototype().texture);
    if (!texture.hasAlpha())
      return structurePtr->getBehaviorModel();

    if (texture.checkAlpha(hitPos, structure.getAnimationPlayer().getCurrentFrame()))
      return structurePtr->getBehaviorModel();
  }
  
  return nullptr;
}
