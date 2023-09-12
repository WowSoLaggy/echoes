#pragma once

#include "Fwd.h"
#include "Layers.h"

#include <LaggySdk/Vector.h>


class Tile
{
public:
  void update(double i_dt);

private:
  std::unordered_map<Layer, StructurePtr> d_structures;
};

using Tiles = std::unordered_map<Sdk::Vector2I, Tile, Sdk::Vector2_hash>;
