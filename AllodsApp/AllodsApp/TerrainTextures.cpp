#include "stdafx.h"
#include "TerrainTextures.h"


const std::string& getTerrainTexture(TerrainType i_type)
{
  static const std::unordered_map<TerrainType, std::string> TerrainTextures{
    { TerrainType::Dirt1, "Dirt1.png" },
    { TerrainType::Dirt2, "Dirt2.png" },
  };

  return TerrainTextures.at(i_type);
}
