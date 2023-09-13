#pragma once

#include "StructurePrototype.h"


class Structure
{
public:
  Structure(const StructurePrototype& i_prototype);

private:
  const StructurePrototype& d_prototype;
};
