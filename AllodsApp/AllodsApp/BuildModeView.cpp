#include "stdafx.h"
#include "BuildModeView.h"

#include "BuildDraftInfo.h"

#include <LaggyDx/App.h>
#include <LaggyDx/ISpriteShader.h>


void BuildModeView::setBuildDraft(const BuildDraftInfo& i_buildDraftInfo)
{
  d_sprite.emplace(Dx::Sprite());
  d_sprite->setTexture(Dx::App::get().getResourceController().getTexture(i_buildDraftInfo.textureName));
  d_sprite->resetSizeToTexture();

  d_allowance = &i_buildDraftInfo.buildAllowed;
}

void BuildModeView::resetBuildDraft()
{
  d_allowance = nullptr;
  d_sprite.reset();
}


void BuildModeView::render(const Dx::ISpriteShader& i_shader) const
{
  if (d_sprite)
    i_shader.draw(*d_sprite);
}
