#pragma once

#include "StructurePrototype.h"


class Structure
{
public:
  Structure(const StructurePrototype& i_prototype);

  [[nodiscard]] const StructurePrototype& getPrototype() const;

private:
  const StructurePrototype& d_prototype;
};
