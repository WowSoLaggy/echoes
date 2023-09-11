#pragma once

#include <LaggyDx/LaggyDxFwd.h>


class BackgroundView
{
public:
  void update(double i_dt);
  void render(const Dx::ISpriteShader& i_shader) const;
};
