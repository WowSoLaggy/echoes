#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/Vector.h>


TileCoord getTileCoords(const Sdk::Vector2I& i_screenPos, const Dx::ICamera2& i_camera);
Sdk::Vector2I getTilePosWorld(const TileCoord& i_tileCoords);
Sdk::Vector2I getTilePosScreen(const TileCoord& i_tileCoords, const Dx::ICamera2& i_camera);
