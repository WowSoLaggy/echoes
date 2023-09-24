#pragma once

#include "Fwd.h"

#include <LaggyDx/MouseKeys.h>
#include <LaggySdk/EventHandler.h>


class BuildManager : public Sdk::EventHandler
{
public:
  BuildManager(Session& i_session);

  bool isInBuildMode() const;
  void setBuildDraft(const StructurePrototype& i_prototype);
  void resetBuildDraft();

  bool isInRemovalMode() const;
  void startRemovalMode();
  void stopRemovalMode();

  void onMouseMove();
  bool onMouseClick(Dx::MouseKey i_key);
  void onMouseRelease(Dx::MouseKey i_key);

private:
  Session& d_session;

  const StructurePrototype* d_buildPrototype = nullptr;
  std::shared_ptr<BuildDraftInfo> d_buildDraftInfo;

  bool d_isMutlibuilding = false;
  bool d_isRemovalMode = false;

  void updateBuildDraft();
  void updateBuildPosition();
  void updateBuildAllowance();
  bool canBeBuilt() const;
  const Tile* getTileForBuildDraft() const;
  bool doesTileHaveLowerLayerWithSupport() const;
  bool doesTileAlreadyHaveTheSameStructure() const;

  void tryBuild();
  void build();

  void tryRemove();
};
