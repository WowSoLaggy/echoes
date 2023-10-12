#pragma once

#include "Fwd.h"
#include "IBehaviorModel.h"

#include <LaggyDx/Animation2Player.h>

#include <LaggySdk/Size.h>


class Entity
{
public:
  Entity(const Prototype& i_prototype);
  virtual ~Entity() = default;

  void update(double i_dt);

  [[nodiscard]] const Prototype& getPrototype() const;

  [[nodiscard]] const Sdk::Size2I& getSize() const;

  [[nodiscard]] Dx::Animation2Player& getAnimationPlayer();
  [[nodiscard]] const Dx::Animation2Player& getAnimationPlayer() const;

  void setBehaviorModel(BehaviorModelPtr i_model);
  [[nodiscard]] BehaviorModelPtr getBehaviorModel() const;

private:
  const Prototype& d_prototype;
  Dx::Animation2Player d_animationPlayer;
  BehaviorModelPtr d_behaviorModel;
};
