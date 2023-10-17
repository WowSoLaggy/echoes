#pragma once

#include "Fwd.h"
#include "TileBaseEntity.h"


class Mount : public TileBaseEntity
{
public:
  Mount();
  Mount(PrototypePtr i_prototype);

  [[nodiscard]] const MountPrototype& getMountPrototype() const;
};
