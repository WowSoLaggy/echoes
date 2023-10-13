#pragma once

#include "BehaviorModels.h"
#include "Fwd.h"
#include "Layers.h"

#include <LaggyDx/ITexture.h>


struct Prototype
{
  virtual ~Prototype() = default;

  PrototypeName name;

  const Dx::ITexture* texture = nullptr;
  BehaviorModel bahaviorModel = BehaviorModel::None;

  bool operator==(const Prototype& i_other) const
  {
    return this->name == i_other.name;
  }
};


struct StructurePrototype : public Prototype
{
  Layer layer;
  bool support = false;
  bool fixture = false;
};


struct MountPrototype : public Prototype
{
};


struct ObjectPrototype : public Prototype
{
};


struct AvatarPrototype : public Prototype
{
};
