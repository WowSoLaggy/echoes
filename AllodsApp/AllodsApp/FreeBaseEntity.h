#pragma once

#include "Entity.h"

#include <LaggySdk/Rect.h>
#include <LaggySdk/Vector.h>


class FreeBaseEntity : public Entity
{
public:
  using Entity::Entity;

  void setPosition(Sdk::Vector2I i_position);
  [[nodiscard]] const Sdk::Vector2I& getPosition() const;

  const Sdk::Vector2I& getSize() const;

  Sdk::RectI getRect() const;

private:
  Sdk::Vector2I d_position;
};
