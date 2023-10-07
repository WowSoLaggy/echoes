#include "stdafx.h"
#include "AnimationUtils.h"

#include "Entity.h"
#include "Prototypes.h"


void AnimationUtils::playAnimation(
  Entity& i_entity, const std::string& i_animationName, std::optional<int> i_times)
{
  const auto& animations = i_entity.getPrototype().texture->getAnimationsMap();
  const auto& animation = animations.at(i_animationName);
  i_entity.getAnimationPlayer().playAnimation(&animation, i_times);
}
