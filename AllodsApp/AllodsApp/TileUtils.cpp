#include "stdafx.h"
#include "TileUtils.h"

#include "Constants.h"

#include <LaggyDx/CursorUtils.h>
#include <LaggyDx/ICamera2.h>


TileCoord TileUtils::getTileCoords(const Sdk::Vector2F& i_absPos)
{
  const int x = static_cast<int>(std::floor((double)i_absPos.x / Constants::TileSize));
  const int y = static_cast<int>(std::floor((double)i_absPos.y / Constants::TileSize));
  return { x, y };
}

TileCoord TileUtils::getTileCoords(const Sdk::Vector2F& i_screenPos, const Dx::ICamera2& i_camera)
{
  const auto absPos = i_screenPos + i_camera.getOffset();
  return getTileCoords(absPos);
}

TileCoord TileUtils::getTileCoordsUnderCursor(const Dx::ICamera2& i_camera)
{
  return getTileCoords(Dx::CursorUtils::getPosition().getVector<float>(), i_camera);
}


Sdk::Vector2F TileUtils::getTilePos(const TileCoord& i_tileCoords)
{
  return i_tileCoords.getVector<float>() * Constants::TileSize;
}

Sdk::Vector2F TileUtils::getTileCenter(const TileCoord& i_tileCoords)
{
  return
    (i_tileCoords * Constants::TileSize).getVector<float>() +
    Sdk::Vector2F{ Constants::TileSize / 2, Constants::TileSize / 2};
}

Sdk::Vector2F TileUtils::getTilePosScreen(const TileCoord& i_tileCoords, const Dx::ICamera2& i_camera)
{
  const auto tilePosLocation = getTilePos(i_tileCoords);
  const auto tilePosScreen = tilePosLocation - i_camera.getOffset();
  return tilePosScreen;
}


Sdk::Vector2F TileUtils::getAbsPosUnderCursor(const Dx::ICamera2& i_camera)
{
  return Dx::CursorUtils::getPosition().getVector<float>() + i_camera.getOffset();
}
