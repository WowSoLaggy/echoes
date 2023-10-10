#pragma once

#include "FixtureLocations.h"

#include <LaggyDx/LaggyDxFwd.h>

#include <LaggySdk/Vector.h>


struct BuildDraftInfo
{
  virtual ~BuildDraftInfo() = default;

  const Dx::ITexture* texture = nullptr;
  bool allowed = false;
  TileCoord tileCoords;
};


struct BuildMountDraftInfo : public BuildDraftInfo
{
  FixtureLocation fixtureLocation = FixtureLocation::Bottom;
};
