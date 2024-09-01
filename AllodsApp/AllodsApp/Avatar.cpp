#include "stdafx.h"
#include "Avatar.h"

#include "Prototypes.h"
#include "Units.h"


Avatar::Avatar()
{
}

Avatar::Avatar(PrototypePtr i_prototype)
  : FreeBaseEntity(i_prototype)
{
}


const AvatarPrototype& Avatar::getAvatarPrototype() const
{
  return dynamic_cast<const AvatarPrototype&>(getPrototype());
}


std::optional<double> Avatar::getTemperature() const
{
  return Units::celsiusToKelvin(36.6);
}
