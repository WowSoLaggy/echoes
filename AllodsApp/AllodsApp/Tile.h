#pragma once

#include "Fwd.h"
#include "Layers.h"

#include <LaggySdk/Vector.h>


using LayersMap = std::map<Layer, StructurePtr>;


class Tile
{
public:
  void update(double i_dt);

  const LayersMap& getLayers() const;

  void setStructure(Layer i_layer, StructurePtr i_structure);

private:
  LayersMap d_layers;
};

using Tiles = std::unordered_map<TileCoord, Tile, Sdk::Vector2_hash>;
