#include "stdafx.h"
#include "AnimationUtils.h"

#include "Structure.h"


void AnimationUtils::playAnimation(
  Structure& i_structure, const std::string& i_animationName, std::optional<int> i_times)
{
  const auto& animations = i_structure.getPrototype().texture->getAnimationsMap();
  const auto& animation = animations.at(i_animationName);
  i_structure.getAnimationPlayer().playAnimation(&animation, i_times);
}
