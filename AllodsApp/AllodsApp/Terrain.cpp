#include "stdafx.h"
#include "Terrain.h"


Terrain::Terrain(const int i_sizeX, const int i_sizeY)
  : d_sizeX(i_sizeX)
  , d_sizeY(i_sizeY)
{
  d_tiles.resize(d_sizeX * d_sizeY, TerrainType::DefaultTerrainType);
}


int Terrain::getSizeX() const
{
  return d_sizeX;
}

int Terrain::getSizeY() const
{
  return d_sizeY;
}


void Terrain::setTerrainType(const TerrainType i_type, const int i_x, const int i_y)
{
  d_tiles[getIndex(i_x, i_y)] = i_type;
}

TerrainType Terrain::getTerrainType(const int i_x, const int i_y) const
{
  return d_tiles[getIndex(i_x, i_y)];
}


int Terrain::getIndex(const int i_x, const int i_y) const
{
  assertCoords(i_x, i_y);
  return i_x + i_y * d_sizeX;
}

void Terrain::assertCoords(const int i_x, const int i_y) const
{
  CONTRACT_EXPECT(0 <= i_x);
  CONTRACT_EXPECT(0 <= i_y);

  CONTRACT_EXPECT(i_x < d_sizeX);
  CONTRACT_EXPECT(i_y < d_sizeY);
}
