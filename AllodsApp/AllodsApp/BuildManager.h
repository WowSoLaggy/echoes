#pragma once

#include "Fwd.h"

#include <LaggySdk/EventHandler.h>


class BuildManager : public Sdk::EventHandler
{
public:
  BuildManager(Session& i_session);

  void setBuildDraft(const StructurePrototype& i_prototype);
  void resetBuildDraft();

  void update();

private:
  Session& d_session;

  const StructurePrototype* d_buildPrototype = nullptr;
  std::shared_ptr<BuildDraftInfo> d_buildDraftInfo;

  void updateBuildPosition();
  void updateBuildAllowance();
  bool canBeBuilt() const;
};
