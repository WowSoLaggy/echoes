#pragma once

#include <LaggySdk/Vector.h>


struct BuildDraftInfo
{
  BuildDraftInfo(const std::string& i_textureName)
    : textureName(i_textureName)
  {
  }

  const std::string& textureName;
  bool allowed = false;
  Sdk::Vector2I position;
};
