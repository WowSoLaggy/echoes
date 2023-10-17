#pragma once

#include "FreeBaseEntity.h"


class Object : public FreeBaseEntity
{
public:
  Object();
  Object(PrototypePtr i_prototype);

  [[nodiscard]] const ObjectPrototype& getObjectPrototype() const;
};
