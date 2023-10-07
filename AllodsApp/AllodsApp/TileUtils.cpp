#include "stdafx.h"
#include "TileUtils.h"

#include "Constants.h"

#include <LaggyDx/CursorUtils.h>
#include <LaggyDx/ICamera2.h>


Sdk::Vector2I TileUtils::getTileCoords(const Sdk::Vector2I& i_screenPos, const Dx::ICamera2& i_camera)
{
  const auto locationPos = i_screenPos + i_camera.getOffset();
  const int x = static_cast<int>(std::floor((double)locationPos.x / Constants::TileSize));
  const int y = static_cast<int>(std::floor((double)locationPos.y / Constants::TileSize));
  return { x, y };
}

TileCoord TileUtils::getTileCoordsUnderCursor(const Dx::ICamera2& i_camera)
{
  return getTileCoords(Dx::CursorUtils::getPosition(), i_camera);
}

Sdk::Vector2I TileUtils::getTilePos(const Sdk::Vector2I& i_tileCoords)
{
  return i_tileCoords * Constants::TileSize;
}

Sdk::Vector2I TileUtils::getTileCenter(const TileCoord& i_tileCoords)
{
  return i_tileCoords * Constants::TileSize + Sdk::Vector2I{ Constants::TileSize / 2, Constants::TileSize / 2};
}

Sdk::Vector2I TileUtils::getTilePosScreen(const Sdk::Vector2I& i_tileCoords, const Dx::ICamera2& i_camera)
{
  const auto tilePosLocation = getTilePos(i_tileCoords);
  const auto tilePosScreen = tilePosLocation - i_camera.getOffset();
  return tilePosScreen;
}
