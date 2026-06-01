#pragma once

#include "Entity.h"

#include <LaggySdk/Rect.h>
#include <LaggySdk/Vector.h>


class FreeBaseEntity : public Entity
{
public:
  using Entity::Entity;

  virtual void pushFields() override;

  void setPosition(Sdk::Vector2F i_position);
  [[nodiscard]] const Sdk::Vector2F& getPosition() const;

  const Sdk::Vector2I& getSize() const;

  Sdk::RectI getRect() const;

private:
  Sdk::Vector2F d_position;
};
