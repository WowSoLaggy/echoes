#pragma once

#include "Fwd.h"
#include "Layers.h"


struct StructurePrototype
{
  PrototypeName name;

  std::string textureName;
  Layer layer;
  bool support = false;

  bool operator==(const StructurePrototype& i_other) const
  {
    return this->name == i_other.name;
  }
};
