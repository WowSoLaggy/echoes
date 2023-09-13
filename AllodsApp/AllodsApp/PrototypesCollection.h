#pragma once

#include "StructurePrototype.h"


class PrototypesCollection
{
public:
  PrototypesCollection() = delete;

  static void load(const fs::path& i_prototypesFolder);

  static const StructurePrototype& getStructurePrototype(const std::string& i_name);
};
