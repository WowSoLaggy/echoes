#pragma once

#include "Prototypes.h"


using MountPrototypesMap = std::unordered_map<PrototypeName, MountPrototype>;
using StructurePrototypesMap = std::unordered_map<PrototypeName, StructurePrototype>;


class PrototypesCollection
{
public:
  static void load(const fs::path& i_prototypesFolder);

  static const MountPrototype& getMountPrototype(const PrototypeName& i_name);
  static const StructurePrototype& getStructurePrototype(const PrototypeName& i_name);

  static const MountPrototypesMap& getMountPrototypes();
  static const StructurePrototypesMap& getStructurePrototypes();

private:
  PrototypesCollection() = delete;

  static void loadMounts(const fs::path& i_prototypesFolder);
  static void loadStructures(const fs::path& i_prototypesFolder);
};
