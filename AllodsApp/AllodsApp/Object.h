#pragma once

#include "Entity.h"

#include <LaggySdk/Vector.h>


class Object : public Entity
{
public:
  Object(const ObjectPrototype& i_prototype);

  [[nodiscard]] const ObjectPrototype& getObjectPrototype() const;

  void setPosition(Sdk::Vector2I i_position);
  [[nodiscard]] const Sdk::Vector2I& getPosition() const;

  const Sdk::Vector2I& getSize() const;

private:
  Sdk::Vector2I d_position;
};
