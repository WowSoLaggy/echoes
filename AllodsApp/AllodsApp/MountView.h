#pragma once

#include "FixtureLocations.h"
#include "Fwd.h"

#include <LaggyDx/Colors.h>
#include <LaggyDx/LaggyDxFwd.h>

#include <LaggySdk/Vector.h>


class MountView
{
public:
  MountView(const Dx::ISpriteShader& i_shader);

  void render(const Fixture& i_fixture, const TileCoord& i_coords) const;
  void render(
    const TileCoord& i_coords, const Dx::ITexture* i_texture,
    FixtureLocation i_fixtureLocation, int i_animationFrame,
    Dx::Color i_color = Dx::Colors::White) const;

private:
  const Dx::ISpriteShader& d_shader;
};
