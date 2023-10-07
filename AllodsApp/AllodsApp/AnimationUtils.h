#pragma once

#include "Fwd.h"


class AnimationUtils
{
public:
  static void playAnimation(
    Entity& i_entity, const std::string& i_animationName, std::optional<int> i_times);

private:
  AnimationUtils() = delete;
};
