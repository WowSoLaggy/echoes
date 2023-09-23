#pragma once

#include "Fwd.h"

#include <LaggyDx/MouseKeys.h>
#include <LaggySdk/EventHandler.h>


class BuildManager : public Sdk::EventHandler
{
public:
  BuildManager(Session& i_session);

  void setBuildDraft(const StructurePrototype& i_prototype);
  void resetBuildDraft();

  void onMouseMove();
  void onMouseClick(Dx::MouseKey i_key);

private:
  Session& d_session;

  const StructurePrototype* d_buildPrototype = nullptr;
  std::shared_ptr<BuildDraftInfo> d_buildDraftInfo;

  void updateBuildDraft();
  void updateBuildPosition();
  void updateBuildAllowance();
  bool canBeBuilt() const;
  const Tile* getTileForBuildDraft() const;
  bool doesTileHaveLowerLayerWithSupport() const;

  void tryBuild();
  void build();
};
