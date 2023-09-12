#pragma once

#include "StructurePrototype.h"


class PrototypesCollection
{
public:
  void load(const fs::path& i_prototypesFolder);

  const StructurePrototype& getStructurePrototype(const std::string& i_name) const;

private:
  std::unordered_map<std::string, StructurePrototype> d_structurePrototypes;
};
