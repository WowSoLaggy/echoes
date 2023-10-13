#pragma once

#include "TileBaseEntity.h"
#include "Fwd.h"


class Mount : public TileBaseEntity
{
public:
  Mount(const MountPrototype& i_prototype);

  [[nodiscard]] const MountPrototype& getMountPrototype() const;
};
