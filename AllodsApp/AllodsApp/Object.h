#pragma once

#include "FreeBaseEntity.h"


class Object : public FreeBaseEntity
{
public:
  Object(const ObjectPrototype& i_prototype);

  [[nodiscard]] const ObjectPrototype& getObjectPrototype() const;
};
