#pragma once

#include "Fwd.h"
#include "Layers.h"

#include <LaggySdk/Vector.h>


class Tile
{
public:
  void update(double i_dt);

  void setStructure(Layer i_layer, StructurePtr i_structure);

private:
  std::unordered_map<Layer, StructurePtr> d_structures;
};

using Tiles = std::unordered_map<TileCoord, Tile, Sdk::Vector2_hash>;
