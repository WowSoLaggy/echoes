#include "stdafx.h"
#include "Object.h"

#include "Prototypes.h"


Object::Object()
{
}

Object::Object(PrototypePtr i_prototype)
  : FreeBaseEntity(i_prototype)
{
}


const ObjectPrototype& Object::getObjectPrototype() const
{
  return dynamic_cast<const ObjectPrototype&>(getPrototype());
}
