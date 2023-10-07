#pragma once

#include "Entity.h"
#include "Fwd.h"


class Mount : public Entity
{
public:
  Mount(const MountPrototype& i_prototype);

  [[nodiscard]] const MountPrototype& getMountPrototype() const;
};
