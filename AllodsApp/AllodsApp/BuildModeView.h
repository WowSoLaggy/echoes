#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/Sprite.h>


class BuildModeView
{
public:
  void setBuildDraft(const BuildDraftInfo& i_buildDraftInfo);
  void resetBuildDraft();

  void render(const Dx::ISpriteShader& i_shader) const;

private:
  std::optional<Dx::Sprite> d_sprite;
  const bool* d_allowance = nullptr;
};
