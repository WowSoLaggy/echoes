#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>


class AvatarsView
{
public:
  void render(const Dx::ISpriteShader& i_shader, const Avatars& i_avatars) const;
};
