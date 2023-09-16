#pragma once

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/Sprite.h>


class BackgroundView
{
public:
  BackgroundView();

  void render(const Dx::ISpriteShader& i_shader, const Dx::ICamera2& i_camera) const;

public:
  Dx::Sprite d_sprite;
  float d_resolutionRatio = 1;
};
