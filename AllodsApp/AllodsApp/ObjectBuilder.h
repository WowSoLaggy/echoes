#pragma once

#include "Fwd.h"


class ObjectBuilder
{
public:
  static bool canBeBuilt(const Location& i_location);
  static void build(Location& i_location);

private:
  ObjectBuilder() = delete;
};
