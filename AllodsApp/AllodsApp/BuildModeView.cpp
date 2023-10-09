#include "stdafx.h"
#include "BuildModeView.h"

#include "BuildDraftInfo.h"
#include "MountView.h"
#include "TileUtils.h"

#include <LaggyDx/App.h>
#include <LaggyDx/ISpriteShader.h>


namespace
{
  Dx::Color getColor(const bool i_allowed)
  {
    Dx::Color BuildAllowedColor{ 0.5f, 1.0f, 0.5f, 1.0f };
    Dx::Color BuildForbiddenColor{ 1.0f, 0.5f, 0.5f, 1.0f };

    return i_allowed ? BuildAllowedColor : BuildForbiddenColor;
  }

} // anonym NS


void BuildModeView::setBuildDraft(std::shared_ptr<BuildDraftInfo> i_buildDraftInfo)
{
  d_buildDraftInfo = i_buildDraftInfo;
}


void BuildModeView::render(const Dx::ISpriteShader& i_shader) const
{
  if (d_buildDraftInfo)
  {
    MountView(i_shader).render(
      d_buildDraftInfo->tileCoords, d_buildDraftInfo->texture,
      d_buildDraftInfo->fixtureLocation, 0, getColor(d_buildDraftInfo->allowed));
  }
}
