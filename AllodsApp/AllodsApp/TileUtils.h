#pragma once

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/Vector.h>


Sdk::Vector2I getTileCoords(const Sdk::Vector2I& i_screenPos, const Dx::ICamera2& i_camera);
Sdk::Vector2I getTilePosWorld(const Sdk::Vector2I& i_tileCoords);
Sdk::Vector2I getTilePosScreen(const Sdk::Vector2I& i_tileCoords, const Dx::ICamera2& i_camera);
