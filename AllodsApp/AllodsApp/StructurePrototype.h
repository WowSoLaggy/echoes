#pragma once

#include "Fwd.h"
#include "Layers.h"

#include <LaggyDx/ITexture.h>


struct StructurePrototype
{
  PrototypeName name;

  const Dx::ITexture* texture = nullptr;
  Layer layer;
  bool support = false;

  bool operator==(const StructurePrototype& i_other) const
  {
    return this->name == i_other.name;
  }
};
