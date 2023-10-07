#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>


class ObjectView
{
public:
  void render(const Dx::ISpriteShader& i_shader, const Objects& i_objects) const;
};
