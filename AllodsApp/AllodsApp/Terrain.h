#pragma once

#include "TerrainType.h"


class Terrain
{
public:
  Terrain(const int i_sizeX, const int i_sizeY);

  int getSizeX() const;
  int getSizeY() const;

  void setTerrainType(const TerrainType i_type, const int i_x, const int i_y);
  TerrainType getTerrainType(const int i_x, const int i_y) const;

private:
  const int d_sizeX = 0;
  const int d_sizeY = 0;
  std::vector<TerrainType> d_tiles;

  int getIndex(const int i_x, const int i_y) const;
  void assertCoords(const int i_x, const int i_y) const;
};
