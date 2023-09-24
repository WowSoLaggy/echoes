#pragma once

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/Vector.h>


struct BuildDraftInfo
{
  const Dx::ITexture* texture = nullptr;
  bool allowed = false;
  TileCoord tileCoords;
};
