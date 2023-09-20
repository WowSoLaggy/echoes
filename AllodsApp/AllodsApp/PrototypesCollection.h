#pragma once

#include "StructurePrototype.h"


class PrototypesCollection
{
public:
  PrototypesCollection() = delete;

  static void load(const fs::path& i_prototypesFolder);

  static const StructurePrototype& getStructurePrototype(const PrototypeName& i_name);

  static const std::unordered_map<PrototypeName, StructurePrototype>& getStructurePrototypes();
};
