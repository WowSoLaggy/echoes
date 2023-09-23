#include "stdafx.h"
#include "Tile.h"


void Tile::update(const double i_dt)
{
}


const LayersMap& Tile::getLayers() const
{
  return d_layers;
}


void Tile::setStructure(const Layer i_layer, StructurePtr i_structure)
{
  CONTRACT_EXPECT(i_structure);
  CONTRACT_EXPECT(d_layers[i_layer] == nullptr);
  d_layers[i_layer] = i_structure;
}

void Tile::resetStructure(const Layer i_layer)
{
  d_layers.erase(i_layer);
}
