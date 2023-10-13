#pragma once

#include "FreeBaseEntity.h"


class Avatar : public FreeBaseEntity
{
public:
  Avatar(const AvatarPrototype& i_prototype);

  [[nodiscard]] const AvatarPrototype& getAvatarPrototype() const;
};
