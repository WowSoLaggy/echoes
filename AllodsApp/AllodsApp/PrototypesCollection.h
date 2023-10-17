#pragma once

#include "Prototypes.h"


using PrototypesMap = std::unordered_map<PrototypeName, PrototypePtr>;


class PrototypesCollection
{
public:
  static void load(const fs::path& i_prototypesFolder);

  static PrototypePtr getAvatarPrototype(const PrototypeName& i_name);
  static PrototypePtr getMountPrototype(const PrototypeName& i_name);
  static PrototypePtr getStructurePrototype(const PrototypeName& i_name);
  static PrototypePtr getObjectPrototype(const PrototypeName& i_name);

  static const PrototypesMap& getAvatarPrototypes();
  static const PrototypesMap& getMountPrototypes();
  static const PrototypesMap& getStructurePrototypes();
  static const PrototypesMap& getObjectPrototypes();

private:
  PrototypesCollection() = delete;

  static void loadAvatars(const fs::path& i_prototypesFolder);
  static void loadMounts(const fs::path& i_prototypesFolder);
  static void loadStructures(const fs::path& i_prototypesFolder);
  static void loadObjects(const fs::path& i_prototypesFolder);
};
