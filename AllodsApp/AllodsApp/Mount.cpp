#include "stdafx.h"
#include "Mount.h"

#include "Prototypes.h"


Mount::Mount()
{
}

Mount::Mount(PrototypePtr i_prototype)
  : TileBaseEntity(i_prototype)
{
}


const MountPrototype& Mount::getMountPrototype() const
{
  return dynamic_cast<const MountPrototype&>(getPrototype());
}
