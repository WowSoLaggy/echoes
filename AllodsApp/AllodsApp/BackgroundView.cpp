#include "stdafx.h"
#include "BackgroundView.h"

#include <LaggyDx/App.h>
#include <LaggyDx/ICamera2.h>
#include <LaggyDx/ISpriteShader.h>


BackgroundView::BackgroundView()
{
  const auto& rc = Dx::App::get().getResourceController();
  d_sprite.setTexture(rc.getTexture("Space.png"));

  const auto& rd = Dx::App::get().getRenderDevice();
  d_sprite.setSize(rd.getResolution());
}


void BackgroundView::render(const Dx::ISpriteShader& i_shader, const Dx::ICamera2& i_camera) const
{
  const auto offset = i_camera.getOffset().getVector<float>() / 8000;
  const auto multiplier = Sdk::Vector2F(2, 1);
  const auto uvOffset = Dx::UvOffset{ offset, multiplier };
  i_shader.draw(d_sprite, &uvOffset, true);
}
