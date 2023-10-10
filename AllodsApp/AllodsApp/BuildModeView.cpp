#include "stdafx.h"
#include "BuildModeView.h"

#include "BuildDraftInfo.h"
#include "MountView.h"
#include "StructureView.h"
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
  if (const auto* mountDraft = getBuildMountDraft())
  {
    MountView(i_shader).render(
      mountDraft->tileCoords, mountDraft->texture,
      mountDraft->fixtureLocation, 0, getColor(mountDraft->allowed));
  }
  else if (const auto* draft = getBuildDraft())
  {
    StructureView(i_shader).render(
      draft->texture, TileUtils::getTilePos(draft->tileCoords),
      0, getColor(draft->allowed));
  }
  else
  {
    CONTRACT_EXPECT(!d_buildDraftInfo);
  }
}


const BuildMountDraftInfo* BuildModeView::getBuildMountDraft() const
{
  return dynamic_cast<const BuildMountDraftInfo*>(d_buildDraftInfo.get());
}

const BuildDraftInfo* BuildModeView::getBuildDraft() const
{
  return d_buildDraftInfo.get();
}
