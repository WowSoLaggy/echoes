#include "stdafx.h"
#include "TileUtils.h"

#include "Constants.h"

#include <LaggyDx/ICamera2.h>


Sdk::Vector2I getTileCoords(const Sdk::Vector2I& i_screenPos, const Dx::ICamera2& i_camera)
{
  const auto worldPos = i_screenPos + i_camera.getOffset();
  const int x = static_cast<int>(std::floor((double)worldPos.x / Constants::TileSize));
  const int y = static_cast<int>(std::floor((double)worldPos.y / Constants::TileSize));
  return { x, y };
}

Sdk::Vector2I getTilePosWorld(const Sdk::Vector2I& i_tileCoords)
{
  return i_tileCoords * Constants::TileSize;
}

Sdk::Vector2I getTilePosScreen(const Sdk::Vector2I& i_tileCoords, const Dx::ICamera2& i_camera)
{
  const auto tilePosWorld = getTilePosWorld(i_tileCoords);
  const auto tilePosScreen = tilePosWorld - i_camera.getOffset();
  return tilePosScreen;
}
