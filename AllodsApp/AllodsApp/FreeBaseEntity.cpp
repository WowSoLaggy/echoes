#include "stdafx.h"
#include "FreeBaseEntity.h"

#include "Prototypes.h"

#include <LaggyDx/ImageDescription.h>


void FreeBaseEntity::pushFields()
{
  Entity::pushFields();

  pushField("position", d_position);
}


void FreeBaseEntity::setPosition(Sdk::Vector2I i_position)
{
  d_position = std::move(i_position);
}

const Sdk::Vector2I& FreeBaseEntity::getPosition() const
{
  return d_position;
}


const Sdk::Vector2I& FreeBaseEntity::getSize() const
{
  return SAFE_DEREF(getPrototype().texture).getDescription().frameSize;
}


Sdk::RectI FreeBaseEntity::getRect() const
{
  const auto p1 = getPosition() - getSize() / 2;
  return { p1, p1 + getSize() };
}
