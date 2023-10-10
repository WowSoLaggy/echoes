#pragma once

#include "Fwd.h"

#include <LaggySdk/Vector.h>


class ObjectBuilder
{
public:
  ObjectBuilder(Location& i_location, const Sdk::Vector2I& i_position, const ObjectPrototype& i_prototype);

  bool canBeBuilt();
  void build();

private:
  Location& d_location;
  const Sdk::Vector2I& d_position;
  const ObjectPrototype& d_prototype;
};
