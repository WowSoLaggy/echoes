#pragma once

#include "Fwd.h"

#include <LaggyDx/MouseKeys.h>

#include <LaggySdk/EventHandler.h>


class BuildManager : public Sdk::EventHandler
{
public:
  BuildManager(Session& i_session);

  bool isInBuildMode() const;
  void setBuildDraft(const Prototype& i_prototype);
  void resetBuildDraft();

  void rotateDraftClockwise();

  bool isInRemovalMode() const;
  void startRemovalMode();
  void stopRemovalMode();

  void onMouseMove();
  bool onMouseClick(Dx::MouseKey i_key);
  void onMouseRelease(Dx::MouseKey i_key);

private:
  Session& d_session;

  const Prototype* d_buildPrototype = nullptr;
  std::shared_ptr<BuildDraftInfo> d_buildDraftInfo;

  bool d_isMutlibuilding = false;
  bool d_isMutliremoving = false;
  std::optional<TileCoord> d_lastRemovedCoords;
  bool d_isRemovalMode = false;

  bool isDraftStructure() const;
  bool isDraftMount() const;
  bool isDraftObject() const;
  const StructurePrototype& getStructurePrototype() const;
  const MountPrototype& getMountPrototype() const;
  const ObjectPrototype& getObjectPrototype() const;

  void updateBuildDraft();
  void updateBuildPosition();
  void updateBuildAllowance();
  bool canBeBuilt() const;
  bool canBeBuiltStructure() const;
  bool canBeBuiltMount() const;
  bool canBeBuiltObject() const;

  void tryBuild();
  void build();
  void buildStructure();
  void buildMount();
  void buildObject();

  void tryRemove();
};
