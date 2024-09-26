#pragma once

#include "Fwd.h"
#include "IAvatarBehavior.h"


class AvatarBehaviorPlayer : public IAvatarBehavior
{
public:
  explicit AvatarBehaviorPlayer(Avatar& i_avatar);

  virtual void update() override;
};
