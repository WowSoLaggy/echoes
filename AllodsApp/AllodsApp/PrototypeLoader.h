#pragma once

#include "Prototypes.h"


class PrototypeLoader
{
public:
  static std::vector<MountPrototype> loadMounts(const fs::path& i_filepath);
  static std::vector<StructurePrototype> loadStructures(const fs::path& i_filepath);
  static std::vector<ObjectPrototype> loadObjects(const fs::path& i_filepath);

private:
  PrototypeLoader() = delete;
};
