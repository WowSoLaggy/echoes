#include "stdafx.h"
#include "Object.h"

#include "Prototypes.h"

#include <LaggyDx/ImageDescription.h>


Object::Object(const ObjectPrototype& i_prototype)
  : Entity(i_prototype)
{
}


const ObjectPrototype& Object::getObjectPrototype() const
{
  return dynamic_cast<const ObjectPrototype&>(getPrototype());
}


void Object::setPosition(Sdk::Vector2I i_position)
{
  d_position = std::move(i_position);
}

const Sdk::Vector2I& Object::getPosition() const
{
  return d_position;
}


const Sdk::Vector2I& Object::getSize() const
{
  return SAFE_DEREF(getPrototype().texture).getDescription().size;
}
