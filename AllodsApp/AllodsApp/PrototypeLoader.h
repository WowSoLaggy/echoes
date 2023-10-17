#pragma once

#include "Prototypes.h"


class PrototypeLoader
{
public:
  static std::vector<PrototypePtr> loadAvatars(const fs::path& i_filepath);
  static std::vector<PrototypePtr> loadMounts(const fs::path& i_filepath);
  static std::vector<PrototypePtr> loadStructures(const fs::path& i_filepath);
  static std::vector<PrototypePtr> loadObjects(const fs::path& i_filepath);

private:
  PrototypeLoader() = delete;
};
