#pragma once

#include "Fwd.h"

#include <LaggySdk/Vector.h>


class ObjectBuilder
{
public:
  ObjectBuilder(Location& i_location, const Sdk::Vector2I& i_position, PrototypePtr i_prototype);

  bool canBeBuilt() const;
  void build() const;

private:
  Location& d_location;
  const Sdk::Vector2I& d_position;
  PrototypePtr d_prototype;

  bool hasStructureAtWallLayer() const;
};
