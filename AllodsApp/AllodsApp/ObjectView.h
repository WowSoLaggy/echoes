#pragma once

#include <LaggyDx/Colors.h>
#include <LaggyDx/LaggyDxFwd.h>

#include <LaggySdk/Vector.h>


class ObjectView
{
public:
  ObjectView(const Dx::ISpriteShader& i_shader);

  void render(
    const Dx::ITexture* i_texture, const Sdk::Vector2F& i_position,
    int i_animationFrame, Dx::Color i_color = Dx::Colors::White) const;

private:
  const Dx::ISpriteShader& d_shader;
};
