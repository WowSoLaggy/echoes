#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/AnimatedSprite.h>


class BuildModeView
{
public:
  void setBuildDraft(std::shared_ptr<BuildDraftInfo> i_buildDraftInfo);

  void render(const Dx::ISpriteShader& i_shader);

private:
  std::optional<Dx::AnimatedSprite> d_sprite;
  std::shared_ptr<BuildDraftInfo> d_buildDraftInfo;
};
