#include "stdafx.h"
#include "TileUtils.h"

#include "Constants.h"

#include <LaggyDx/CursorUtils.h>
#include <LaggyDx/ICamera2.h>


Sdk::Vector2I TileUtils::getTileCoords(const Sdk::Vector2I& i_screenPos, const Dx::ICamera2& i_camera)
{
  const auto worldPos = i_screenPos + i_camera.getOffset();
  const int x = static_cast<int>(std::floor((double)worldPos.x / Constants::TileSize));
  const int y = static_cast<int>(std::floor((double)worldPos.y / Constants::TileSize));
  return { x, y };
}

TileCoord TileUtils::getTileCoordsUnderCursor(const Dx::ICamera2& i_camera)
{
  return getTileCoords(Dx::CursorUtils::getPosition(), i_camera);
}

Sdk::Vector2I TileUtils::getTilePosWorld(const Sdk::Vector2I& i_tileCoords)
{
  return i_tileCoords * Constants::TileSize;
}

Sdk::Vector2I TileUtils::getTilePosScreen(const Sdk::Vector2I& i_tileCoords, const Dx::ICamera2& i_camera)
{
  const auto tilePosWorld = getTilePosWorld(i_tileCoords);
  const auto tilePosScreen = tilePosWorld - i_camera.getOffset();
  return tilePosScreen;
}
