#pragma once

#include "Fwd.h"


class StructureBuilder
{
public:
  StructureBuilder(Location& i_location, const TileCoord& i_tileCoords, const StructurePrototype& i_prototype);

  bool canBeBuilt() const;
  void build() const;

private:
  Location& d_location;
  const TileCoord& d_tileCoords;
  const StructurePrototype& d_prototype;

  bool doesTileHaveLowerLayerWithSupport() const;
  bool doesTileAlreadyHaveTheSameStructure() const;
  bool doesWallBlocksFurniture() const;
};
