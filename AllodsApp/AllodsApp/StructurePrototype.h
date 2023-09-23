#pragma once

#include "Fwd.h"
#include "Layers.h"


struct StructurePrototype
{
  PrototypeName name;

  std::string textureName;
  Layer layer;
  bool support = false;
};
