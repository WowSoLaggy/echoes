#include "stdafx.h"
#include "Tile.h"


void Tile::update(const double i_dt)
{
}


void Tile::setStructure(const Layer i_layer, StructurePtr i_structure)
{
  CONTRACT_EXPECT(i_structure);
  CONTRACT_EXPECT(d_structures[i_layer] == nullptr);
  d_structures[i_layer] = i_structure;
}
