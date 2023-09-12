#pragma once

#include "StructurePrototype.h"


class StructurePrototypeLoader
{
public:
  static std::vector<StructurePrototype> load(const fs::path& i_filepath);
};
