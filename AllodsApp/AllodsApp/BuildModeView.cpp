#include "stdafx.h"
#include "BuildModeView.h"

#include "BuildDraftInfo.h"

#include <LaggyDx/App.h>
#include <LaggyDx/ISpriteShader.h>


namespace
{
  Sdk::Vector4F BuildAllowedColor{ 0.5f, 1.0f, 0.5f, 1.0f };
  Sdk::Vector4F BuildForbiddenColor{ 1.0f, 0.5f, 0.5f, 1.0f };

} // anonym NS


void BuildModeView::setBuildDraft(std::shared_ptr<BuildDraftInfo> i_buildDraftInfo)
{
  d_buildDraftInfo = i_buildDraftInfo;

  if (d_buildDraftInfo)
  {
    d_sprite.emplace(Dx::Sprite());
    d_sprite->setTexture(Dx::App::get().getResourceController().getTexture(d_buildDraftInfo->textureName));
    d_sprite->resetSizeToTexture();
  }
  else
    d_sprite.reset();
}


void BuildModeView::render(const Dx::ISpriteShader& i_shader)
{
  if (d_sprite)
  {
    CONTRACT_EXPECT(d_buildDraftInfo);

    d_sprite->setColor(d_buildDraftInfo->allowed ? BuildAllowedColor : BuildForbiddenColor);
    d_sprite->setPosition(d_buildDraftInfo->position);

    i_shader.draw(*d_sprite);
  }
}
