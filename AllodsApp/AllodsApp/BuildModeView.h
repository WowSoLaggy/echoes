#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/AnimatedSprite.h>


class BuildModeView
{
public:
  void setBuildDraft(std::shared_ptr<BuildDraftInfo> i_buildDraftInfo);

  void render(const Dx::ISpriteShader& i_shader) const;

private:
  std::shared_ptr<BuildDraftInfo> d_buildDraftInfo;
};
