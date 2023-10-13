#include "stdafx.h"
#include "Avatar.h"

#include "Prototypes.h"


Avatar::Avatar(const AvatarPrototype& i_prototype)
  : FreeBaseEntity(i_prototype)
{
}


const AvatarPrototype& Avatar::getAvatarPrototype() const
{
  return dynamic_cast<const AvatarPrototype&>(getPrototype());
}
