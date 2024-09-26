#pragma once

#include "Fwd.h"


class IAvatarBehavior
{
public:
  explicit IAvatarBehavior(Avatar& i_avatar);
  virtual ~IAvatarBehavior() = default;

  virtual void update() {}

private:
  Avatar& d_avatar;
};
