#pragma once


struct BuildDraftInfo
{
  BuildDraftInfo(const std::string& i_textureName)
    : buildAllowed(false)
    , textureName(i_textureName)
  {
  }

  bool buildAllowed = false;
  const std::string& textureName;
};
