#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>

#include <LaggySdk/Vector.h>


class TileUtils
{
public:
  static TileCoord getTileCoords(const Sdk::Vector2I& i_absPos);
  static TileCoord getTileCoords(const Sdk::Vector2I& i_screenPos, const Dx::ICamera2& i_camera);
  static TileCoord getTileCoordsUnderCursor(const Dx::ICamera2& i_camera);
  
  static Sdk::Vector2I getTilePos(const TileCoord& i_tileCoords);
  static Sdk::Vector2I getTileCenter(const TileCoord& i_tileCoords);
  static Sdk::Vector2I getTilePosScreen(const TileCoord& i_tileCoords, const Dx::ICamera2& i_camera);

  static Sdk::Vector2I getAbsPosUnderCursor(const Dx::ICamera2& i_camera);

private:
  TileUtils() = delete;
};
