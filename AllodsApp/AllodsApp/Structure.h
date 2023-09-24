#pragma once

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

private:
  const StructurePrototype& d_prototype;
  Dx::Animation2Player d_animationPlayer;
};
