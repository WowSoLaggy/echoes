#include "stdafx.h"
#include "ObjectBuilder.h"


ObjectBuilder::ObjectBuilder(Location& i_location, const Sdk::Vector2I& i_position, const ObjectPrototype& i_prototype)
  : d_location(i_location)
  , d_position(i_position)
  , d_prototype(i_prototype)
{
}


bool ObjectBuilder::canBeBuilt()
{
  return true;
}

void ObjectBuilder::build()
{
}
