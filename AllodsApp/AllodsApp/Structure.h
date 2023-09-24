#pragma once

#include "IBehaviorModel.h"
#include "StructurePrototype.h"

#include <LaggyDx/Animation2Player.h>


class Structure
{
public:
  Structure(const StructurePrototype& i_prototype);

  void update(double i_dt);

  [[nodiscard]] const StructurePrototype& getPrototype() const;

  [[nodiscard]] Dx::Animation2Player& getAnimationPlayer();
  [[nodiscard]] const Dx::Animation2Player& getAnimationPlayer() const;

  void setBehaviorModel(BehaviorModelPtr i_model);
  [[nodiscard]] BehaviorModelPtr getBehaviorModel() const;

private:
  const StructurePrototype& d_prototype;
  Dx::Animation2Player d_animationPlayer;
  BehaviorModelPtr d_behaviorModel = nullptr;
};
